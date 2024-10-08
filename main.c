/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:45:50 by labderra          #+#    #+#             */
/*   Updated: 2024/10/02 14:36:45 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mini	*init_shell(char **argv, char **envp)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->argv = argv;
	mini->envp = copy_environmet(envp);
	mini->envp_dictionary = copy_split_environment(mini->envp);
	mini->path = get_full_path(mini->envp);
	if (!mini->path)
		return (NULL);
	mini->status = 0;
	mini->tkn_list = NULL;
	mini->cmd_list = NULL;
	return (mini);
}

void handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_sigquit(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
	exit(131);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_mini		*mini;
	(void)argv;
	mini = init_shell(argv, envp);
	if (argc != 1 || !mini)
		return (1);
	signal(SIGINT, handle_sigint);
	//signal(SIGQUIT, handle_sigquit);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("MininiShell :\\>");
		if (!str)
		{
			printf("%s", "exit\n");
			break ;
		}
		add_history(str);
		lexer(mini, str);
		parser(mini);
		//run_export(mini, NULL);
		exec_line(mini);
		
		free_commands_and_tokens(mini);
		

		free(str);
	}
	free_split(mini->path);
	free_split(mini->envp);
	free(mini);
	return (70);
}
