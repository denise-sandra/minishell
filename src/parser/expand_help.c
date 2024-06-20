/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:32:46 by sandra            #+#    #+#             */
/*   Updated: 2024/06/20 14:30:39 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_and_add_to_list(char *before_var, t_token **new_list)
{
	char	**split_env;
	int		i;

	split_env = ft_split(before_var, ' ');
	free(before_var);
	i = 0;
	while (split_env[i])
	{
		tok_list(split_env[i], STRING, new_list);
		i++;
	}
	free_tab(split_env);
}

static void	handle_before_var(char **before_var, char *env_value)
{
	char	*concatenated;

	concatenated = NULL;
	if (*before_var)
	{
		concatenated = ft_strjoin(*before_var, env_value);
		free(*before_var);
		free(env_value);
		*before_var = concatenated;
	}
	else
		*before_var = env_value;
}

static char	*expand_variable(t_mini *mini, char *temp_str, int *len)
{
	char	*env_name;
	char	*env_value;
	char	*after_s;

	env_name = get_env_name(&temp_str[*len]);
	if (ft_strncmp(env_name, "?", 1) == 0)
	{
		env_value = ft_itoa(mini->exit_status);
		if (ft_strlen(env_name) > 1)
		{
			after_s = ft_strnstr(env_name, "?", ft_strlen(env_name));
			env_value = ft_strjoin_frees1(env_value, after_s + 1);
			if (env_value == NULL)
			{
				free(env_name);
				return (ft_error(mini, NULL, strerror(errno)), NULL);
			}
			*len += ft_strlen(env_name) + 1;
		}
		else
			*len += 2;
	}
	else
	{
		env_value = get_env_value(mini->env, env_name);
		if (!env_value)
			env_value = ft_strdup("");
		*len += env_name_len(&temp_str[*len]) + 1;
	}
	free(env_name);
	return (env_value);
}

void	expand_outside_dq(t_mini *mini, t_token **cur, t_token **new_list)
{
	char	*temp_str;
	char	*before_var;
	char	*env_value;
	int		j;

	temp_str = (*cur)->value;
	before_var = NULL;
	j = 0;
	while (temp_str[j])
	{
		if (temp_str[j] != '$' || (temp_str[j] == '$' && !temp_str[j + 1])
			|| (temp_str[j] == '$' && temp_str[j + 1] && (temp_str[j + 1] == ' '
					|| ft_isdigit(temp_str[j + 1]))))
		{
			before_var = ft_strjoin_char(before_var, temp_str[j]);
			j++;
		}
		else
		{
			env_value = expand_variable(mini, temp_str, &j);
			if (env_value == NULL)
				return ;
			handle_before_var(&before_var, env_value);
		}
	}
	if (before_var)
		split_and_add_to_list(before_var, new_list);
}

void	expand_inside_dq(t_mini *mini, char **str)
{
	char	*temp_str;
	char	*new_str;
	char	*env_value;
	int		i;

	temp_str = *str;
	new_str = NULL;
	i = 0;
	while (temp_str[i])
	{
		if (temp_str[i] == '$' && temp_str[i + 1] && (temp_str[i + 1] != ' '
				&& !ft_isdigit(temp_str[i + 1])))
		{
			env_value = expand_variable(mini, temp_str, &i);
			new_str = ft_strjoin_free(new_str, env_value);
		}
		else
		{
			new_str = ft_strjoin_char(new_str, temp_str[i]);
			i++;
		}
	}
	free(*str);
	*str = new_str;
}
