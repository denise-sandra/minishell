/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/22 22:52:46 by deniseerjav      ###   ########.fr       */
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

char	*replace_env_value(t_minishell *minishell, char *token, int env_var)
{
	char	*new_token;
	int		size;
	int		i;
	int		name_len;

	i = 0;
	name_len = 0;
	size = ft_strlen(token);
	while (i < env_var)
	{
		if (token[name_len] == '$' && token[name_len + 1])
		{
			size = calcule_new_size(minishell, token + name_len, size);
			i++;
		}
		name_len++;
	}
	new_token = fill_new_token(minishell, token, size);
	free(token);
	return (new_token);
}

int	count_env_var(char *token)
{
	int	i;
	int	env;
	
	i = 0;
	env = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1])
			env++;
		i++;
	}
	return (env);
}
