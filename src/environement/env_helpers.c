/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/06/11 13:16:24 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strncmp(temp->name, name, ft_strlen(name)) == 0)
		{
			dup = ft_strdup(temp->value);
			return (dup);
		}
		temp = temp->next;
	}
	free(name);
	empty = malloc(sizeof(char));
	if (empty == NULL)
		return (NULL);
	empty[0] = '\0';
	return (empty);
}

void	replace_env(t_lst_env *env, char *name)
{
	t_lst_env	*temp;
	t_lst_env	*next;
	t_lst_env	*prev;

	temp = env;
	prev = NULL;
	next = NULL;
	while (temp)
	{
		if (ft_strncmp(temp->name, name, ft_strlen(name)) == 0)
		{
			free(temp->name);
			free(temp->value);
			if (temp->next)
				next = temp->next;
			free(temp);
			prev->next = next;
			return ;
		}
		prev = temp;	
		temp = temp->next;
	}
}

// int	calcule_new_size(t_minishell *minishell, char *token, int old_size)
// {
// 	int		new_size;
// 	char	*name;
// 	char	*value;
// 	int		value_len;

// 	old_size = old_size - (env_name_len(token) + 1);
// 	name = return_env_str(token);
// 	if (name == NULL)
// 		ft_error("Malloc in return_env_value", minishell);
// 	value = get_env_value(minishell->env, name);
// 	if (value == NULL)
// 		value_len = 0;
// 	else
// 		value_len = ft_strlen(value);
// 	new_size = old_size + value_len;
// 	free(name);
// 	return (new_size);
// }

// int	env_name_len(char *token)
// {
// 	int	i;

// 	i = 1;
// 	while (token[i] && token[i] != 32 && token[i] != 34 \
// 			&& token[i] != 39 && token[i] != '$')
// 		i++;
// 	return (i - 1);
// }

int	is_env_value(t_minishell *minishell, char *value)
{
	t_lst_env	*temp;
	char		*str;

	temp = minishell->env;
	while (temp)
	{
		str = ft_strnstr(value, temp->value, ft_strlen(value));
		if (str && ft_strncmp(str, temp->value, ft_strlen(str)) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}
