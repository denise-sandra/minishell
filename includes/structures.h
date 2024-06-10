/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:55 by skanna            #+#    #+#             */
/*   Updated: 2024/06/10 13:28:29 by derjavec         ###   ########.fr       */
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
	TEXT,
	D_Q,
	S_Q,
	EXP,
	IN,
	OUT,
	OPT,
	PIPE,
	CHAR,
	EMPTY,
	ENV,
	COMMAND,
	BUILTIN,
	END,
	HEREDOC,
	APPEND,
	IN_FILE,
	OUT_FILE,
	ARG,
	ERROR
}	t_type;

typedef struct s_pretok
{
	char			c;
	t_type			type;
	struct s_pretok	*next;
}	t_pretok;

typedef struct s_token
{
	char			**tab;
	char			*value;
	t_type			type;
	t_type			prev;
	int				order;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell
{
	t_lst_env	*env;
	t_token		*token;
	t_pretok	*pretok;
	int			token_count;
	int			last_exit_status;
	int			redirect_in;
	int			redirect_out;
	char		*builtin[7];
	char		*input_file;
	char		*output_file;
}	t_minishell;

#endif