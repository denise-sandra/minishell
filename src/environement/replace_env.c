/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/27 15:03:09 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  replace_env_utils(t_minishell *minishell, t_lst_token **split_token, int env, int size)
{
	t_lst_token *tmp;
    int i;
    int j;
    int single_q;
    
	tmp = *split_token;
	j = 0;
	single_q = 0;
	while (tmp && j < env)
	{
		i = 0;
		if (tmp->type == ENV)
		{
			while (tmp->value[i])
			{
				if (tmp->value[i] == '$')
				{
					size = calcule_new_size(minishell, tmp->value + i, size);
					j++;
				}
			i++;
			}
		}
		tmp = tmp->next;
	}
	return (size);
}

char	*replace_env_value(t_minishell *minishell, t_lst_token **split_token, int env)
{
	char	*new_token;
	int		size;

	size = ft_lst_len(split_token);
	size = replace_env_utils(minishell, split_token, env, size);
	printf("new size: %d  token: %s\n", size, *(split_token)->value);
	new_token = return_new_token(minishell, split_token, size);
	free(token);
	return (new_token);
}