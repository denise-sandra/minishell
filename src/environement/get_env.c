/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/22 14:25:42 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_lst_env *env, char *name)
{
	t_lst_env	*temp;

	if (name == NULL || env == NULL)
		return (NULL);
	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->name, name, ft_strlen(name)) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
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

int	is_env_name(t_minishell *minishell, char *token, int i)
{
	char	*name;

	if (token[i] == '$')
	{
		if (i == 0)
			return (1);
		name = return_env_str(token + i);
		if (name == NULL)
			ft_error("Malloc in return_env_value", minishell);
		if (get_env_value(minishell->env, name) != NULL)
		{
			if (check_quotes_for_env(token + i) == 1)
			{
				free(name);
				return (1);
			}
		}
		free(name);
	}
	return (0);
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
		if (is_env_name(minishell, token, name_len) == 1)
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

int	count_env_var(t_minishell *minishell, char *token)
{
	int	i;
	int	j;
	int	count;
	int	env_var;

	count = count_character(token, '$');
	if (count == 0)
		return (0);
	i = 0;
	j = 0;
	env_var = 0;
	while (i < count)
	{
		while (token[j])
		{
			if (is_env_name(minishell, token, j) == 1)
			{
				env_var++;
				i++;
			}	
			j++;
			i++;
		}		
	}		
	return (env_var);
}
