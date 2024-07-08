/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/07/08 16:59:52 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	longer_len(char *s1, char *s2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}

char	*get_env_value(t_lst_env *env, char *name)
{
	t_lst_env	*temp;
	char		*empty;
	char		*dup;

	if (name == NULL || env == NULL)
		return (NULL);
	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->name, name, longer_len(name, temp->name)) == 0)
		{
			dup = ft_strdup(temp->value);
			return (dup);
		}
		temp = temp->next;
	}
	empty = malloc(sizeof(char));
	if (empty == NULL)
		return (NULL);
	empty[0] = '\0';
	return (empty);
}

char	*get_env_name(char *token)
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

int	env_name_len(char *token)
{
	int	i;

	i = 1;
	while (token[i] && token[i] != 32 && token[i] != 34 \
			&& token[i] != 39 && token[i] != '$')
		i++;
	return (i - 1);
}

char	*expand_variable(t_mini *mini, char *temp_str, int *len)
{
	char	*env_name;
	char	*env_value;

	env_name = get_env_name(&temp_str[*len]);
	env_value = get_env_value(mini->env, env_name);
	free(env_name);
	if (!env_value)
		env_value = ft_strdup("");
	*len += env_name_len(&temp_str[*len]) + 1;
	return (env_value);
}
