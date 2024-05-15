/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:55 by skanna            #+#    #+#             */
/*   Updated: 2024/05/15 12:48:12 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_lst_env
{
	char	*name;
	char	*value;
	struct s_lst_env *next;
}	t_lst_env;

typedef enum e_tokentype
{
	TOKEN_ENV,
	TOKEN_COMMAND,
	TOKEN_SPECIAL_COMMAND,
	TOKEN_OPS,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
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
	t_token			**token;
	int				token_count;
	int				last_exit_status;
	int				redirect_in;
	int				redirect_out;
	char			*special_commands[2];     //build_in
	char			*input_file;
	char			*output_file;
}	t_minishell;

#endif