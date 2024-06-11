/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:22:03 by sandra            #+#    #+#             */
/*   Updated: 2024/06/11 15:49:43 by skanna           ###   ########.fr       */
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

	env_name = get_env_name(&temp_str[*len]);
	env_value = get_env_value(mini->env, env_name);
	free(env_name);
	if (!env_value)
		env_value = ft_strdup("");
	*len += env_name_len(&temp_str[*len]) + 1;
	return (env_value);
}

static void	expand_outside_dq(t_mini *mini, t_token **cur, t_token **new_list)
{
	char	*temp_str;
	char	*before_var;
	char	*env_value;
	int		j;

	temp_str = (*cur)->value;
	before_var = NULL;
	j = 0;
	printf("exp outside dq: %s\n", temp_str);
	while (temp_str[j] && temp_str[j] != '$')
	{
		before_var = ft_strjoin_char(before_var, temp_str[j]);
		j++;
	}
	while (temp_str[j] == '$')
	{
		env_value = expand_variable(mini, temp_str, &j);
		handle_before_var(&before_var, env_value);
	}
	if (before_var)
		split_and_add_to_list(before_var, new_list);
}

static void	expand_inside_dq(t_mini *mini, char **str)
{
	char	*temp_str;
	char	*new_str;
	char	*env_value;
	int		i;

	temp_str = *str;
	new_str = NULL;
	i = 0;
	printf("exp inside dq: %s\n", temp_str);
	while (temp_str[i])
	{
		printf("str in expand: %c\n", temp_str[i]);
		if (temp_str[i] == '$')
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

void	expand_env_vars(t_mini *mini, t_token *list)
{
	t_token	*cur;
	t_token	*new_list;
	t_token	*temp;

	cur = list;
	new_list = NULL;
	while (cur)
	{
		temp = cur->next;
		if ((cur->type == STRING || cur->type == D_Q || cur->type == S_Q) && ft_strchr(cur->value, '$'))
		{
			printf("---entered exp en var--- %s\n", cur->value);
			if (cur->type == D_Q)
			{
				expand_inside_dq(mini, &cur->value);
				tok_list(cur->value, STRING, &new_list);
			}
			else if (cur->type == S_Q)
				tok_list(cur->value, STRING, &new_list);
			else
				expand_outside_dq(mini, &cur, &new_list);
		}
		else
			tok_list(cur->value, cur->type, &new_list);
		free(cur->value);
		free (cur);
		cur = temp;
	}
	mini->token = new_list;
}
