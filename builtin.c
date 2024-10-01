/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:42:34 by jormoral          #+#    #+#             */
/*   Updated: 2024/10/01 11:43:15 by jormoral         ###   ########.fr       */
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



void run_export(t_mini *mini, t_command *cmd)
{
	int	i;
	char ***env;
	int c;
	char **temp;
	(void)cmd;
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
}
