/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/24 23:29:44 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  replace_env_utils(t_minishell *minishell, char *token, int env, int size)
{
    int i;
    int j;
    int single_q;
    
    while (i < env)
	{
		while (token[j])
		{
            if (token[j] == 34)
                single_q = 0;
			if (token[j] == 39)
				single_q++;
			if (token[j] == '$' && token[j + 1] && single_q % 2 == 0)
			{
				size = calcule_new_size(minishell, token + j, size);
				i++;
			}
			j++;
		}	
	}
}

char	*replace_env_value(t_minishell *minishell, char *token, int env)
{
	char	*new_token;
	int		size;

	size = ft_strlen(token);
	size = replace_env_utils(minishell, token, env, size);
	printf("new size: %d  token: %s\n", size, token);
	new_token = return_new_token(minishell, token, size);
	free(token);
	return (new_token);
}