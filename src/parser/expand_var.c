/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:22:03 by sandra            #+#    #+#             */
/*   Updated: 2024/07/23 10:48:57 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_and_add_to_list(char *before_var, t_token **new_list)
{
	char	**split_env;
	int		i;

	split_env = ft_split(before_var, ' ');
	free(before_var);
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

static int	expand_outside_dq(t_mini *mini, t_token **cur, t_token **new_list)
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
			before_var = ft_strjoin_char(before_var, temp_str[j++]);
			if (!before_var)
			{
				if (env_value)
					free(env_value);
				return (-1);
			}
		}
		else
		{
			env_value = expand_var(mini, temp_str, &j);
			if (!env_value)
			{
				if (before_var)
					free(before_var);
				return (-1);
			}
			if (handle_before_var(&before_var, env_value) != 0)
				return (-1);
		}
	}
	if (before_var)
	{
		if (split_and_add_to_list(before_var, new_list) != 0)
			return (-1);
	}
	return (0);
}

static int	expand_inside_dq(t_mini *mini, char **str)
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
		if (temp_str[i] == '$' && temp_str[i + 1] && temp_str[i + 1] != ' '
				&& (ft_isalpha(temp_str[i + 1]) == 1 || temp_str[i + 1] == '?'))
		{
			env_value = expand_var(mini, temp_str, &i);
			if (!env_value)
				return (-1);
			new_str = ft_strjoin_free(new_str, env_value);
			if (!new_str)
				return (-1);
		}
		else
		{
			new_str = ft_strjoin_char(new_str, temp_str[i]);
			if (!new_str)
				return (-1);
			i++;
		}
	}
	free(*str);
	*str = new_str;
	return (0);
}

static int	expand_and_add(t_mini *mini, t_token *cur, t_token **new_list)
{
	if (cur->type == D_Q)
	{
		if (expand_inside_dq(mini, &cur->value) != 0)
			return (-1);
		if (tok_list(cur->value, STRING, new_list) != 0)
			return (-1);
	}
	else if (cur->type == S_Q)
	{
		if (tok_list(cur->value, STRING, new_list) != 0)
			return (-1);
	}
	else
	{
		if (expand_outside_dq(mini, &cur, new_list) != 0)
			return (-1);
	}
	return (0);
}

int	expand_env_vars(t_mini *mini, t_token *list)
{
	t_token	*cur;
	t_token	*new_list;
	t_token	*temp;

	cur = list;
	new_list = NULL;
	while (cur)
	{
		temp = cur->next;
		if ((cur->type == STRING || cur->type == D_Q || cur->type == S_Q)
			&& ft_strchr(cur->value, '$'))
		{
			if (expand_and_add(mini, cur, &new_list) != 0)
			{
				mini->token = new_list;
				return (ft_error(mini, NULL, strerror(errno)), 1);
			}
		}	
		else
		{
			if (cur->type == D_Q || cur->type == S_Q)
				cur->type = STRING;
			if (tok_list(cur->value, cur->type, &new_list) == 1)
			{
				mini->token = new_list;
				return (ft_error(mini, NULL, strerror(errno)), 1);
			}
		}
		free(cur->value);
		free (cur);
		cur = temp;
	}
	mini->token = new_list;
	return (0);
}
