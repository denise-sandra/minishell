/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:55 by skanna            #+#    #+#             */
/*   Updated: 2024/07/09 13:44:11 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_lst_env
{
	char				*name;
	char				*value;
	struct s_lst_env	*next;
}	t_lst_env;

typedef enum e_type
{
	WHITE,
	ERROR,
	D_Q,
	S_Q,
	SLASH,
	IN,
	OUT,
	OPT,
	PIPE,
	CHAR,
	EMPTY,
	STRING,
	HERE,
	LIM,
	APP,
	ENV,
	COMMAND,
}	t_type;

typedef struct s_pretok
{
	char			c;
	t_type			type;
	struct s_pretok	*next;
}	t_pretok;

typedef struct s_token
{
	char			*value;
	t_type			type;
	char			**cmd_tab;
	struct s_token	*next;
}	t_token;

typedef struct s_order
{
	t_token	*prev;
	t_token	*redir_head;
	t_token	*redir_tail;
	t_token	*cmd_head;
	t_token	*cmd_tail;
}	t_order;

typedef struct s_minishell
{
	t_lst_env	*env;
	t_lst_env	*export;
	char		**env_char;
	t_token		*token;
	t_pretok	*pretok;
	t_order		*order;
	int			exit_status;
	int			should_exit;
	int			cmd_count;
	int			mod_env;
	int			error;
	int			*inv_fd;
	int			*fd_in;
	int			*fd_out;
	int			(*tube)[2];
	int			here_fd[2];
	pid_t		*pid;
}	t_mini;

#endif