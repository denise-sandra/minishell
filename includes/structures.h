/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:55 by skanna            #+#    #+#             */
/*   Updated: 2024/05/10 16:31:05 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_env_var
{
     char *name;
     char *value;
}t_env_var;

typedef struct s_environement
{
     t_env_var    vars[100];
     int       count;
}t_environement;

typedef enum e_tokentype
{
	TOKEN_COMMAND,
	TOKEN_ARG,
	TOKEN_OPS,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_END
}	t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*value;
}	t_token;

#endif