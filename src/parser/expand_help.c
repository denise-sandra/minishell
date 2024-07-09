/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:32:46 by sandra            #+#    #+#             */
/*   Updated: 2024/07/09 11:14:16 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_before_var(char **before_var, char *env_value)
{
	char	*concatenated;

	concatenated = NULL;
	if (*before_var)
	{
		concatenated = ft_strjoin(*before_var, env_value);
		free(*before_var);
		if (!concatenated)
			return (-1);
		*before_var = concatenated;
	}
	else
		*before_var = env_value;
	return (0);
}

static char	*expand_error_status(t_mini *mini, int *len, char *name)
{
	char	*value;
	char	*after_s;

	value = ft_itoa(mini->exit_status);
	if (!value)
		return (NULL);
	if (ft_strlen(name) > 1)
	{
		after_s = ft_strnstr(name, "?", ft_strlen(name));
		value = ft_strjoin_frees1(value, after_s + 1);
		if (value == NULL)
			return (NULL);
		*len += ft_strlen(name) + 1;
	}
	else
		*len += 2;
	return (value);
}

char	*expand_var(t_mini *mini, char *temp_str, int *len)
{
	char	*name;
	char	*value;

	name = get_env_name(&temp_str[*len]);
	if (!name)
		return (NULL);
	if (ft_strncmp(name, "?", 1) == 0)
	{
		value = expand_error_status(mini, len, name);
		if (!value)
			return (free(name), NULL);
	}
	else
	{
		value = get_env_value(mini->env, name);
		if (!value)
		{
			value = ft_strdup("");
			if (!value)
				return (free(name), NULL);
		}
		*len += env_name_len(&temp_str[*len]) + 1;
	}
	free(name);
	return (value);
}
