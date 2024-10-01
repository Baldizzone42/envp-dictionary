/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:07:06 by labderra          #+#    #+#             */
/*   Updated: 2024/10/01 10:54:31 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*triple_strjoin(char const *s1, char const *s2, char const *s3)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
				+ ft_strlen(s3) + 1));
	if (!p)
		return (NULL);
	while (*s1)
		p[i++] = *s1++;
	while (*s2)
		p[i++] = *s2++;
	while (*s3)
		p[i++] = *s3++;
	p[i] = '\0';
	return (p);
}


int	run_command(t_mini *mini, t_command *cmd)
{
	if (!ft_strncmp(cmd->arg_array[0], "echo", ft_strlen(cmd->arg_array[0])))
		cmd->exit_status = run_echo(mini, cmd);
	else if (!ft_strncmp(cmd->arg_array[0], "pwd", ft_strlen(cmd->arg_array[0])))
		cmd->exit_status = run_pwd(mini, cmd);	
  	/* else if (!ft_strncmp(cmd->arg_array[0], "export", ft_strlen(cmd->arg_array[0])))
		run_export(mini, cmd); */
	/*
	else if (!ft_strncmp(s, "unset", ft_strlen(s)))
		run_unset(cmd);
	else if (!ft_strncmp(s, "env", ft_strlen(s)))
		run_env(cmd);
	else if (!ft_strncmp(s, "exit", ft_strlen(s)))
		run_exit(cmd); */
	else
		return (-1);
	return (0);
}


void	run_execve_command(t_mini *mini, t_command *cmd)
{
	char	**aux;
	char	*path_cmd;
	int		i;
	
	i = 0;
	aux = mini->path;
	path_cmd = triple_strjoin(".", "/", cmd->arg_array[0]);
	if(path_cmd && access(path_cmd, X_OK) == 0)
		execve(path_cmd, cmd->arg_array, mini->envp);
	free(path_cmd);
	while(aux[i])
	{
		path_cmd = triple_strjoin(aux[i], "/", cmd->arg_array[0]);
		if(path_cmd && access(path_cmd, X_OK) == 0)
			execve(path_cmd, cmd->arg_array, mini->envp);
		i++;
		free(path_cmd);
	}
	if (cmd->arg_array && cmd->arg_array[0])
		perror("Command not found");
}

void	exec_child_process(t_mini *mini, int p_in, int p_out, t_command *cmd)
{
	dup2(p_in, STDIN_FILENO);
	dup2(p_out, STDOUT_FILENO);
	close(p_in);
	close(p_out);
	if (cmd->infile != -1)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile != -1)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	run_execve_command(mini, cmd);
}

/* static void	wait_process(t_mini *mini)
{
	t_command	*cmd;

	cmd = mini->cmd_list;
	while (cmd)
	{
		waitpid(cmd->pid, &(cmd->exit_status), 0);
		cmd = cmd->next;
	}
} */

void	exec_line(t_mini *mini)
{
	int			fd[2];
	int			aux[2];
	t_command	*cmd;

	cmd = mini->cmd_list;
	aux[0] = dup(STDIN_FILENO);
	aux[1] = dup(STDOUT_FILENO);
	while (cmd && cmd->next)
	{
		if (pipe(fd) == -1)
			perror("pipe");
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		cmd->exit_status = run_command(mini, cmd);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		cmd = cmd->next;
	}
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	if (cmd)
	{
		dup2(aux[1], STDOUT_FILENO);
		close(aux[1]);
		cmd->exit_status = run_command(mini, cmd);
		dup2(aux[0], STDIN_FILENO);
		close(aux[0]);

	}
}
