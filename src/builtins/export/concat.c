/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/08/09 16:42:43 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_name(t_lst_env *lst, char *name)
{
	int	name_len;

	name_len = ft_strchr_int(name, '=');
	if (name_len == -1)
		name_len = ft_strlen(name);
	while (lst)
	{
		if (ft_strncmp(lst->name, name, name_len) == 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

char	*concat_env(t_mini *mini, char *name, char *new_value)
{
	char	*old_value;
	char	*res;
	int		len;

	len = ft_strlen(name);
	name[len - 1] = '\0';
	old_value = get_env_value(mini->env, name);
	if (!old_value)
		return (NULL);
	res = ft_strjoin(old_value, new_value);
	free (old_value);
	if (!res)
		return (NULL);
	return (res);
}

int	add_env_helper(t_mini *mini, char **new_env)
{
	t_lst_env	*new_node;

	free_env_node(mini, mini->env, new_env[0]);
	new_node = ft_lstnew_env(new_env[0], new_env[1]);
	free_tab(new_env);
	if (new_node == NULL)
		return (-1);
	ft_lstadd_back_env(&mini->env, new_node);
	if (mini->mod_env == 1)
		free_tab(mini->env_char);
	mini->env_char = list_to_tab(mini);
	return (0);
}
