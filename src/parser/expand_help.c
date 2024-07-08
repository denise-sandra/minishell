/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:32:46 by sandra            #+#    #+#             */
/*   Updated: 2024/07/06 14:57:00 by deniseerjav      ###   ########.fr       */
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
		if (!concatenated)
			return (1);
		free(*before_var);
		free(env_value);
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
		return (ft_error(mini, NULL, strerror(errno)), NULL);
	if (ft_strlen(name) > 1)
	{
		after_s = ft_strnstr(name, "?", ft_strlen(name));
		value = ft_strjoin_frees1(value, after_s + 1);
		if (value == NULL)
			return (ft_error(mini, NULL, strerror(errno)), NULL);
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
		return (ft_error(mini, NULL, strerror(errno)), NULL);
	if (ft_strncmp(name, "?", 1) == 0)
	{
		value = expand_error_status(mini, len, name);
		if (!value)
			return (NULL);
	}
	else	
	{
		value = get_env_value(mini->env, name);
		if (!value)
			value = ft_strdup("");
		*len += env_name_len(&temp_str[*len]) + 1;
	}
	free(name);
	return (value);
}
