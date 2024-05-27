/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:55 by skanna            #+#    #+#             */
/*   Updated: 2024/05/27 18:33:18 by sandra           ###   ########.fr       */
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

//src
t_minishell		*init_minishell(char **envp);


//utils
void			ft_error(char *msg, t_minishell *minishell);
char			**ft_split_1st_token(char const *s, char c);
char			**pars_path(t_minishell *minishell);
void	          erase_quotes(t_minishell *minishell, int i);
char	          *erase_all_quotes(char *word);
char	          *erase_outer_quotes(char *word);
void			clean_token(t_minishell *minishell);
void			clean_minishell(t_minishell *minishell);
t_lst_env		*ft_new_node(char *name, char *value);
t_lst_env		*ft_last(t_lst_env *lst);
void			ft_add_back(t_lst_env **lst, t_lst_env *new);

//environement
t_lst_env		*fill_env_struct(char **envp, t_minishell *minishell);
char			*get_env_value(t_lst_env *env, char *name);
int	is_env_value(t_minishell *minishell, int i);
char	        *replace_env_value(t_minishell *minishell, char *token, int env_var);
int             count_env_var(t_lst_token **split_token);
int         	env_name_len(char *token);
char	        *return_env_str(char *token);
int	            check_quotes_for_env(char *token);
int		        calcule_new_size(t_minishell *minishell, char *token, int old_size);
char	*return_new_token(t_minishell *minishell, t_lst_token **split_token);


//lexer
void			tokenize_input(char *input, t_minishell *minishell);
int	            *check_quotes(char *input);
int	            is_normal_command(t_minishell *minishell, t_token *token);
int	            is_special_command(t_minishell *minishell, t_token *token);

//parser
void           parser(t_minishell *minishell);
char	        *erase_extra_quotes(char *str, int len);
void	        tag_token(t_minishell *minishell);
t_lst_token     *ft_lstnew_t(void *content);
void	        ft_lstadd_back_t(t_lst_token **lst, t_lst_token *new);
int		        ft_lst_len(t_lst_token **lst);
void	        ft_lstdelone_t(t_lst_token *lst, void (*del)(void *));
void	        ft_lstclear_t(t_lst_token **lst, void (*del)(void *));
t_lst_token    **split_token_in_nodes(t_minishell *minishell, char *str, int len);

//exec
void			execution(t_minishell *minishell);
void			execute_special_command(t_minishell *minishell, char *command);

//builtin fucntions
void            echo_command(t_minishell *minishell);
void			export_command(t_minishell *minishell);
void			env_command(t_minishell *minishell);
void			exit_cmd(t_minishell *minishell, char *input);

#endif