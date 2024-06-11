/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:55 by skanna            #+#    #+#             */
/*   Updated: 2024/06/11 02:40:47 by sandra           ###   ########.fr       */
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
void		ft_error(char *msg, t_mini *minishell);
void		check_malloc_error(t_mini *mini, void *elem, char *msg, int e);
char		**split_env_vars(char const *s, char c);
void		clean_pretokens(t_mini *minishell);
void		clean_token_list(t_token **list);
void		clean_minishell(t_mini *minishell);
char		*ft_strjoin_free(char *s1, char *s2);

//env
t_lst_env	*ft_lstnew_env(char *name, char *value);
t_lst_env	*ft_lstlast_env(t_lst_env *lst);
void		ft_lstadd_back_env(t_lst_env **lst, t_lst_env *new);

//lexer
void		lexer(char *input, t_mini *mini);
void		tag_in_quotes(t_mini *mini, t_pretok *close_quote);
void		remove_spaces(t_mini *mini);

//parser2
void		parser(t_mini *mini);
void		tokenize_redirs(t_mini *mini, t_pretok **cur, t_token **list);
void		expand_env_vars(t_mini *mini, t_token *token);
void		parse_commands(t_mini *mini);
int			tok_list(char *s, int type, t_token **lst);
t_token		*tok_new_node(char *content, int type);
void		tok_addback(t_token **lst, t_token *new);
char		*ft_strjoin_char(char *s, char c);

//environement
t_lst_env	*fill_env_struct(char **envp, t_mini *minishell);
char		*get_env_value(t_lst_env *env, char *name);
int			is_env_value(t_mini *minishell, char *value);
int			env_name_len(char *token);
char		*get_env_name(char *token);
int			calcule_new_size(t_mini *minishell, char *token, int old_size);

//exec
void		execution(t_mini *minishell);
void		execute_builtin(t_mini *minishell, char *command);

//builtin fucntions
void		echo_command(t_mini *minishell);
void		export_command(t_mini *minishell);
void		env_command(t_mini *minishell);
void		exit_cmd(t_mini *minishell, char *input);

#endif