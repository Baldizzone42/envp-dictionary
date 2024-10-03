/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:42:34 by jormoral          #+#    #+#             */
/*   Updated: 2024/10/02 19:03:50 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_pwd(t_mini *mini, t_command *cmd)
{
	//quizas tengo que mandarle t_mini para que pueda sacar el pwd
	//de la copia del enviroment
	// y en vez de retornar un entero que se guarde mini->status
	char *pwd;
	(void)mini;
	(void)cmd;
	pwd = getcwd(NULL, 0);
	if(!pwd)
		return (1);
	else
	{
		printf("%s\n", pwd);
		free (pwd);
		return (0);
	}
}

int run_echo(t_mini *mini, t_command *cmd)
{
	int nflag;
	(void)mini;
	int i;
	int x;
	x = 1;
	i = 1;
	nflag = 0;
	while(cmd->arg_array[1][x] && cmd->arg_array[1][0] == '-')
	{
		if(cmd->arg_array[1][x] != 'n')
		{
			nflag = 0;
			break;
		}
		x++;
		nflag = 1;
	}
	if(nflag)
		i++;
	while(cmd->arg_array[i])
	{
		printf("%s", cmd->arg_array[i]);
		if(cmd->arg_array[i + 1])
			printf(" ");
		i++;
	}
	if(nflag == 0)
		printf("\n");
	return(0);
} 



/* void run_export(t_mini *mini, t_command *cmd)
{
	if(cmd->arg_array && !cmd->arg_array[1])
		only_export(mini, cmd);
	else
	{
		mini
	}
		
} */

/* void only_export(t_mini *mini, t_command *cmd)
{
	int		c;
	int		i;
	char	***env;
	char	**temp;
	
	env =  mini->envp_dictionary;
	i = 0;
	c = 0;
	while(env[i] && env[i + 1])
	{
		c = 0;
		while(env[i][0][c] == env[i + 1][0][c])
		{
			c++;
		}
		if(env[i][0][c] > env[i + 1][0][c])
		{
			temp = env[i];
			env[i]= env[i + 1];
			env[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	i = 0; 
	while(env[i])
	{
		printf("declare -x %s=\"%s\"\n", env[i][0], env[i][1]);	
		i++;
	}
} */

/* int run_env(t_mini *mini, t_command *cmd)
{
	t_mini	*aux;
	int		i;

	i = 0;
	aux = mini;
	if(!aux->envp)
		return(1);
	while(aux->envp && aux->envp[i])
	{
		printf("%s\n", aux->envp[i]);
		i++;
	}
	return(0);
} */

/* int run_unset(t_mini *mini, t_command *cmd)
{
	int i;
	int c;
	int	j;
	int	len;
	char **new_envp;

	len = 0;
	while(mini->envp[len])
		i++;
	new_envp = ft_calloc((i + 1),sizeof(char *));
	i = 0;
	while(mini->envp[i])
	{
		c = 1;
		while(cmd->arg_array[c])
		{
			if(!ft_strncmp(mini->envp[i], cmd->arg_array[c], ft_strlen(cmd->arg_array[c])));
			{
				free(mini->envp[i]);
				i++;
			}
			c++;
		}
		if(!cmd->arg_array[c])
		{
			new_envp[]
			i++;
		}
		
	}
} */

long long	ft_atoll(const char *str)
{
	int	sign;
	long long	acc;

	sign = 1;
	acc = 0;
	while (*str == '\n' || *str == '\t' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		acc = acc * 10 + *str - 48;
		str++;
	}
	return (sign * acc);
}

void run_exit(t_mini *mini, t_command *cmd)
{
	long long	result;
	(void)mini;
	result = 0;
	if(cmd->arg_array && !cmd->arg_array[1])
		exit(0);
	if(cmd->arg_array && cmd->arg_array[1])
	{
		result = ft_atoll(cmd->arg_array[1]);
	}
	exit(result % 256);
}
