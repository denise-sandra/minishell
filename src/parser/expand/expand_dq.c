/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:22:03 by sandra            #+#    #+#             */
/*   Updated: 2024/07/26 19:06:44 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_env_value(t_mini *mini, char *str, char **bef, int *j)
{
	char	*env_value;

	env_value = expand_var(mini, str, j);
	if (!env_value)
	{
		if (*bef)
			free(*bef);
		return (NULL);
	}
	if (handle_before_var(bef, env_value) != 0)
		return (NULL);
	return (env_value);
}

static int	check_before_and_expand(t_mini *mini, char *str, int *j, char **bef)
{
	char	*env_value;

	env_value = NULL;
	if (str[*j] != '$' || (str[*j] == '$' && !str[*j + 1])
		|| (str[*j] == '$' && str[*j + 1] && (str[*j + 1] == ' '
				|| ft_isdigit(str[*j + 1]))))
	{
		*bef = ft_strjoin_char(*bef, str[(*j)++]);
		if (!*bef)
		{
			if (env_value)
				free(env_value);
			return (-1);
		}
	}
	else
	{
		env_value = expand_env_value(mini, str, bef, j);
		if (!env_value)
			return (-1);
	}
	return (0);
}

int	expand_outside_dq(t_mini *mini, t_token **cur, t_token **new_list)
{
	char	*temp_str;
	char	*bef;
	int		j;

	temp_str = (*cur)->value;
	bef = NULL;
	j = 0;
	while (temp_str[j])
	{
		if (check_before_and_expand(mini, temp_str, &j, &bef) != 0)
			return (-1);
	}
	if (bef)
	{
		if (split_and_add_to_list(bef, new_list) != 0)
			return (-1);
	}
	return (0);
}

static char	*exp_in_dq_ut(t_mini *ms, char *str, char **new, int *i)
{
	char	*env_value;

	env_value = expand_var(ms, str, i);
	if (!env_value)
		return (NULL);
	*new = ft_strjoin_free(*new, env_value);
	if (!*new)
		return (NULL);
	return (*new);
}

int	expand_inside_dq(t_mini *mini, char **str)
{
	char	*temp_str;
	char	*new_str;
	int		i;

	temp_str = *str;
	i = 0;
	new_str = NULL;
	while (temp_str[i])
	{
		if (temp_str[i] == '$' && temp_str[i + 1] && temp_str[i + 1] != ' '
			&& (ft_isalpha(temp_str[i + 1]) == 1 || temp_str[i + 1] == '?'))
			new_str = exp_in_dq_ut(mini, temp_str, &new_str, &i);
		else
		{
			new_str = ft_strjoin_char(new_str, temp_str[i]);
			i++;
		}
		if (!new_str)
			return (-1);
	}
	free(*str);
	*str = new_str;
	return (0);
}
