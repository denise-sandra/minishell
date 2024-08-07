/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:32:46 by sandra            #+#    #+#             */
/*   Updated: 2024/07/26 18:36:53 by deniseerjav      ###   ########.fr       */
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
		free (env_value);
		if (!concatenated)
			return (-1);
		*before_var = concatenated;
	}
	else
	{
		*before_var = ft_strdup(env_value);
		free (env_value);
		if (!*before_var)
			return (-1);
	}
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
	if (name[0] == '?')
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

int	split_and_add_to_list(char *bef, t_token **new_list)
{
	char	**split_env;
	int		i;

	split_env = ft_split(bef, ' ');
	free(bef);
	if (!split_env)
		return (-1);
	i = 0;
	while (split_env[i])
	{
		if (tok_list(split_env[i], STRING, new_list) != 0)
			return (free_tab(split_env), -1);
		if (split_env [i + 1])
		{
			if (tok_list(" ", WHITE, new_list) != 0)
				return (free_tab(split_env), -1);
		}
		i++;
	}
	free_tab(split_env);
	return (0);
}
