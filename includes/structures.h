/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:55 by skanna            #+#    #+#             */
/*   Updated: 2024/06/10 21:30:24 by sandra           ###   ########.fr       */
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
	EXP,
	IN,
	OUT,
	OPT,
	PIPE,
	CHAR,
	EMPTY,//lexer etiqueta hasta aca
	STRING,
	HEREDOC,
	APPEND,
	ENV,
	COMMAND,//no creo que sea necesario
	BUILTIN,//no creo que sea necesario
	ARG//no creo que sea necesario
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
	t_token		*token;
	t_pretok	*pretok;
	int			exit_status;
	int			error;
	int			redirect_in;
	int			redirect_out;
	char		*builtin[7];
	char		*input_file;
	char		*output_file;
}	t_mini;

#endif