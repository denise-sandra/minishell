/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:55 by skanna            #+#    #+#             */
/*   Updated: 2024/08/12 09:19:07 by skanna           ###   ########.fr       */
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
# include <string.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "structures.h"
# include "../libft/Includes/libft_extended.h"

extern int	g_sig;

t_mini		*init_minishell(char **envp);

//clean & error
void		ft_error(t_mini *minishell, char *msg, char *error_msg);
void		print_custom(char *msg);
void		error_cleanup(t_mini *minishell);
char		**split_env_vars(char const *s, char c);
void		clean_pretokens(t_mini *minishell);
void		clean_env_exp(t_mini *minishell, int id);
void		clean_token_list(t_token **list);
void		clean_minishell(t_mini *minishell);
void		clean_fd(t_mini *minishell);

//env
t_lst_env	*ft_lstnew_env(char *name, char *value);
t_lst_env	*ft_lstlast_env(t_lst_env *lst);
void		ft_lstadd_back_env(t_lst_env **lst, t_lst_env *new);
int			count_elements(t_mini *mini);
int			longer_len(char *s1, char *s2);

//lexer
void		lexer(char *input, t_mini *mini);
void		tag_in_quotes(t_mini *mini, t_pretok *close_quote);
void		remove_spaces(t_mini *mini);

//parser
void		parser(t_mini *mini);
void		tokenize_redirs(t_mini *mini, t_pretok **cur, t_token **list);
int			prep_heredoc(t_mini *mini);
void		update_cmd(t_mini *mini, t_token **c, t_token **p, t_token **new);
void		tok_delone(t_token **lst, t_token **prev);
int			expand_env_vars(t_mini *mini, t_token *token);
char		*expand_var(t_mini *mini, char *temp_str, int *len);
int			expand_inside_dq(t_mini *mini, char **str);
int			expand_outside_dq(t_mini *mini, t_token **cur, t_token **new_list);
int			split_and_add_to_list(char *before_var, t_token **new_list);
int			order_tok_list(t_mini *mini);
void		order_redirs(t_mini *mini);
int			parse_commands(t_mini *mini);
int			last_error_checks(t_mini *mini);
int			tok_list(char *s, int type, t_token **lst);
t_token		*tok_new_node(char *content, int type);
void		tok_addback(t_token **lst, t_token *new);
int			handle_before_var(char **before_var, char *env_value);
int			check_white(t_mini *mini);
int			check_slash(t_mini *mini);
void		join_tok(t_mini *mini, t_token **tmp, t_token **prev);
void		tokenize_strings(t_mini *mini, t_pretok **cur, t_token **list);
void		tokenize_quotes(t_mini *ms, t_pretok **cur, \
			t_token **lst, t_type q);
void		tokenize_slash(t_mini *mini, t_pretok **cur, t_token **list);
void		tokenize_pipes_n_empty(t_mini *mini, t_pretok **cur, \
			t_token **list);

//environement
t_lst_env	*fill_env_struct(char **envp, t_mini *minishell);
char		*get_env_value(t_lst_env *env, char *name);
int			is_env_value(t_mini *minishell, char *value);
int			env_name_len(char *token);
char		*get_env_name(char *token);
void		free_env_node(t_mini *mini, t_lst_env *env, char *name);
t_lst_env	*copy_list(t_lst_env *lst);
char		**no_env(t_mini *mini);
void		init_export(t_mini *mini);

//exec
void		execution(t_mini *minishell);
void		cmd_exec(t_mini *mini, t_token *tmp);
int			cmd_exec_utils(t_mini *mini, t_token *tmp, char **paths);
int			is_abs_or_relative(t_mini *mini, t_token *tmp, char **paths);
int			handle_shlvl(t_mini *mini);
int			is_builtin(char *command);
void		execute_builtin(t_mini *mini, int builtin, t_token *cur);
int			malloc_fds(t_mini *mini);
int			ft_dup(t_mini *mini, int i);
int			dup_tubes(t_mini *mini, int i);
void		fill_fd(t_mini *mini, t_token *tmp);
int			process_here_line(int *hd_pipe, char *line, const char *eof);
char		*get_infile(t_mini *mini, t_token *token, int i, char *msg);
void		get_outfile(t_mini *mini, t_token *token, int i);
int			is_accessible(t_mini *mini, t_token *cur);
void		builtin_in_parent(t_mini *mini, int builtin);
void		exec_in_child(t_mini *mini, t_token *tmp);
void		close_fd_and_wait(t_mini *mini);
void		close_all_fd(t_mini *mini);
void		close_all_tubes(t_mini *mini);
void		close_if_inv_fd(t_mini *mini, int j);
char		*get_dynamic_prompt(void);
char		*get_name(t_token *tmp);
char		*get_shebang(t_mini *ms, int script);

//builtin functions
void		echo_command(t_mini *mini, t_token *cur);
void		export_command(t_mini *mini, t_token *cur);
void		add_var_to_list(t_mini *mini, t_token *cur);
int			add_env(t_mini *mini, char *new_var);
int			add_env_helper(t_mini *mini, char **new_env);
char		*concat_env(t_mini *mini, char *name, char *new_value);
int			find_name(t_lst_env *lst, char *name);
char		**list_to_tab(t_mini *mini);
void		env_command(t_mini *minishell, t_token *cur);
void		exit_cmd(t_mini *mini, char **cmd_tab);
int			check_signs(t_mini *mini, char *arg);
void		pwd_cmd(t_mini *mini);
void		cd_cmd(t_mini *mini, t_token *cur);
void		go_back(t_mini *mini);
void		update_env_cd(t_mini *mini);
void		update_export_cd(t_mini *mini);
void		unset_cmd(t_mini *mini, t_token *cur);

// //signals
void		close_here_fd(t_mini *mini);
int			handle_sig_int(t_mini *mini);
void		check_sigs(t_mini *mini);
void		sigs_empty(void);
void		sigs_in_line(void);
void		sigs_ignore(void);
void		sigs_here(void);

#endif