/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:55 by skanna            #+#    #+#             */
/*   Updated: 2024/06/03 14:35:58 by derjavec         ###   ########.fr       */
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
	SYMBOL,
	OPEN_S_Q,
	CLOSE_S_Q,
	OPEN_D_Q,
	CLOSE_D_Q,
	TEXT,
	ENV,
	COMMAND,
	BUILTIN,
	OPS,
	REDIR_IN,
	REDIR_OUT,
	END,
	HEREDOC,
	APPEND,
	ARG,
	OTHER
}	t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*sub_token;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell
{
	t_lst_env	*env;
	t_token		*token;
	int			token_count;
	int			last_exit_status;
	int			redirect_in;
	int			redirect_out;
	char		*builtin[6];     //builtin
	char		*input_file;
	char		*output_file;
}	t_minishell;

#endif