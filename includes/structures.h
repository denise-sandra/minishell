/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:55 by skanna            #+#    #+#             */
/*   Updated: 2024/06/25 13:49:46 by derjavec         ###   ########.fr       */
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
	IN,
	OUT,
	OPT,
	PIPE,
	CHAR,
	EMPTY,
	STRING,
	HERE,
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

typedef struct s_minishell
{
	t_lst_env	*env;
	t_lst_env	*export;
	char		**env_char;
	t_token		*token;
	t_pretok	*pretok;
	int			exit_status;
	int			should_exit;
	int			cmd_count;
	int			mod_env;
	int			error;
	int			*fd_in;
	int			*fd_out;
	int			(*tube)[2];
	int			here_fd[2];
	pid_t		*pid;
}	t_mini;

#endif