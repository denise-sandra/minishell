/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/23 23:52:37 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calcule_new_size(t_minishell *minishell, char *token, int old_size)
{
	int		new_size;
	char	*name;
	char	*value;
	int		value_len;

	old_size = old_size - (env_name_len(token) + 1);
	name = return_env_str(token);
	if (name == NULL)
		ft_error("Malloc in return_env_value", minishell);
	value = get_env_value(minishell->env, name);
	if (value == NULL)
		value_len = 0;
	else
		value_len = ft_strlen(value);
	new_size = old_size + value_len;
	free(name);
	return (new_size);
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

int	is_env_value(t_minishell *minishell, int i)
{
	t_lst_env	*temp;
	char	*str;
	char	*value;

	value = minishell->token[i]->value;
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
