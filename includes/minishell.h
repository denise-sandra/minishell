/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:55 by skanna            #+#    #+#             */
/*   Updated: 2024/06/07 15:38:07 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structures.h"
# include "../libft/Includes/libft_extended.h"

# define SIGNAL

//clean & error
void		ft_error(char *msg, t_minishell *minishell);
char		**split_env_vars(char const *s, char c);
void		clean_pretokens(t_minishell *minishell);
void		clean_subtokens(t_token *sub_token);
void		clean_token_list(t_token *token);
void		clean_minishell(t_minishell *minishell);
char		*ft_strjoin_free(char *s1, char *s2);

//env
t_lst_env	*ft_lstnew_env(char *name, char *value);
t_lst_env	*ft_lstlast_env(t_lst_env *lst);
void		ft_lstadd_back_env(t_lst_env **lst, t_lst_env *new);

//lexer
void			lexer(char *input, t_minishell *mini);
void		parse_quotes(t_minishell *mini, t_pretok *close_quote);
void		remove_spaces(t_minishell *mini);

//parser2
t_token		*tok_new_node(char *content);
void		tok_addback(t_token **lst, t_token *new);

//environement
t_lst_env	*fill_env_struct(char **envp, t_minishell *minishell);
char		*get_env_value(t_lst_env *env, char *name);
int			is_env_value(t_minishell *minishell, char *value);
int			env_name_len(char *token);
char		*return_env_str(char *token);
int			calcule_new_size(t_minishell *minishell, char *token, int old_size);

//exec
void		execution(t_minishell *minishell);
void		execute_builtin(t_minishell *minishell, char *command);

//builtin fucntions
void		echo_command(t_minishell *minishell);
void		export_command(t_minishell *minishell);
void		env_command(t_minishell *minishell);
void		exit_cmd(t_minishell *minishell, char *input);

#endif