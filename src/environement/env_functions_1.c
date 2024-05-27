/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/27 14:07:46 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_lst_env *env, char *name)
{
	t_lst_env	*temp;
	char	*empty;

	if (name == NULL || env == NULL)
		return (NULL);
	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->name, name, ft_strlen(name)) == 0)
			return (temp->value);
		temp = temp->next;
	}
	empty = malloc(sizeof(char));
	if (empty == NULL)
		return (NULL);
	empty[0] = '\0';
	return (empty);
}

char	*return_env_str(char *token)
{
	int		letters;
	char	*env;

	letters = env_name_len(token);
	env = malloc((letters + 1) * sizeof(char));
	if (env == NULL)
		return (NULL);
	ft_strlcpy(env, token + 1, letters + 1);
	return (env);
}

int	count_env_var_utils(char *token)
{
	int	single_q;
	int	i;
	int	env;
	
	i = 0;
	single_q = 0;
	env = 0;
	while (token[i])
	{
		if (token [i] == 39)
			single_q++;
		if (token[i] == '$' && token[i + 1] && single_q % 2 == 0)
			env++;
		i++;
	}
	return (env);
}

int	count_env_var(t_lst_token **split_token)
{
	t_lst_token *tmp;
	int	i;
	int	env;
	
	tmp = *split_token;
	while (tmp)
	{
		i = 0;
		if (ft_strchr_int(tmp->value, '$') == 1 \
			&& ft_strchr_order(tmp->value, 39, 34) == 1)
			env = count_env_var_utils(tmp->value);
		else
		{
			env = 0;
			while (tmp->value[i])
			{
				if (tmp->value[i] == '$' && tmp->value[i + 1])
					env++;
				i++;
			}
		}
	}
	return (env);
}
