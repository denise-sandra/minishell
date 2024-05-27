/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:55 by skanna            #+#    #+#             */
/*   Updated: 2024/05/27 14:32:59 by deniseerjav      ###   ########.fr       */
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

typedef struct s_lst_token
{
	t_quotetype			type;
	char				*value;
	struct s_lst_token	*next;
	//struct s_lst_token	*prev;
}	t_lst_token;

typedef enum e_quotetype
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	OPEN_S_QUOTES,
	CLOSE_S_QUOTES,
	OPEN_D_QUOTES,
	CLOSE_D_QUOTES,
	TEXT,
	ENV,
	OTHER
}	t_quotetype;

typedef enum e_tokentype
{
	TOKEN_ENV,
	TOKEN_COMMAND,
	TOKEN_SPECIAL_COMMAND,
	TOKEN_OPS,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_OPEN_QUOTES,
	TOKEN_END,
	TOKEN_HEREDOC,
	TOKEN_ARG

}	t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*value;
	int			order;
}	t_token;

typedef struct s_minishell
{
	t_lst_env	*env;
	t_token		**token;
	int			token_count;
	int			last_exit_status;
	int			redirect_in;
	int			redirect_out;
	char		*special_commands[6];     //builtin
	char		*input_file;
	char		*output_file;
}	t_minishell;

#endif