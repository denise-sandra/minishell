/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/21 22:00:05 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		calcule_new_size(t_minishell *minishell, char *token, int old_size)
{
	int	new_size;
	int	name_len;
	char	*value;
	int	value_len;

	name_len = env_name_len(token);
	value = return_env_str(minishell, token);
	value = get_env_value(minishell->env, value);
	value_len = ft_strlen(value);
	new_size = old_size - (name_len + 1) + value_len;
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

int	check_quotes_for_env(char *token)
{
	int	*quotes;

	quotes = check_quotes(token);
	if (quotes[0] == 0 && quotes[1] == 0)
		return (1);
	if (token[ft_strlen(token)] == 34)
		return (1);
	if (token[ft_strlen(token)] == 39)
		return (0);
	return (0);
}