/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jormoral <jormoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:04:43 by labderra          #+#    #+#             */
/*   Updated: 2024/10/02 14:34:57 by jormoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_tkn
{
	int				tkn_type;
	char			*tkn;
	struct s_tkn	*next;
}				t_tkn;

typedef struct s_command
{
	char				*path;
	char 				**arg_array;
	int					infile;
	int					outfile;
	int					exit_status;
	int					pid;
	struct s_command	*next;
}						t_command;

typedef struct s_mini
{
	char		**argv;
	char		**envp;
	char		***envp_dictionary;
	char		**path;
	int			status;
	t_tkn		*tkn_list;
	t_command	*cmd_list;
}				t_mini;



char	**get_full_path(char **envp);

void	free_split(char **str);
void	free_list(t_tkn **tkn_list);
void	free_commands_and_tokens(t_mini *mini);
char	*join_before_line(char *prefix, char *line);

void	lexer(t_mini *mini, char *str);
void	parser(t_mini *mini);
void	exec_line(t_mini *mini);

void	insert_variable_value(t_mini *mini, char **str);
char	*check_syntax(t_mini *mini);
char	**add_str_to_array(char *str, char **list);
char	**copy_environmet(char **envp);
char	***copy_split_environment(char **envp);

int		run_pwd(t_mini *mini, t_command *cmd);
int		run_echo(t_mini *mini, t_command *cmd);
void	run_export(t_mini *mini, t_command *cmd);
void 	run_exit(t_mini *mini, t_command *cmd);

#endif