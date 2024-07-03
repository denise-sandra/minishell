/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:22:03 by sandra            #+#    #+#             */
/*   Updated: 2024/07/03 13:27:33 by derjavec         ###   ########.fr       */
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

static void	expand_outside_dq(t_mini *mini, t_token **cur, t_token **new_list)
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
			before_var = ft_strjoin_char(before_var, temp_str[j++]);
		else
		{
			env_value = expand_var(mini, temp_str, &j);
			if (env_value == NULL)
				return ;
			handle_before_var(&before_var, env_value);
		}
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
	while (temp_str[i])
	{
		if (temp_str[i] == '$' && temp_str[i + 1] && (temp_str[i + 1] != ' '
				&& !ft_isdigit(temp_str[i + 1])))
		{
			env_value = expand_var(mini, temp_str, &i);
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

static void	expand_and_add(t_mini *mini, t_token *cur, t_token **new_list)
{
	if (cur->type == D_Q)
	{
		expand_inside_dq(mini, &cur->value);
		tok_list(cur->value, STRING, new_list);
	}
	else if (cur->type == S_Q)
		tok_list(cur->value, STRING, new_list);
	else
		expand_outside_dq(mini, &cur, new_list);
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
		if ((cur->type == STRING || cur->type == D_Q || cur->type == S_Q)
			&& ft_strchr(cur->value, '$'))
		{
			expand_and_add(mini, cur, &new_list);
		}
		else
		{
			if (cur->type == D_Q || cur->type == S_Q)
				cur->type = STRING;
			tok_list(cur->value, cur->type, &new_list);
		}
		free(cur->value);
		free (cur);
		cur = temp;
	}
	mini->token = new_list;
}
