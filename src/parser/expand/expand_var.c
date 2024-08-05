/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:22:03 by sandra            #+#    #+#             */
/*   Updated: 2024/08/05 17:40:07 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	if_no_dollar(t_mini *mini, t_token *cur, t_token	**new_list)
{
	if (ft_strncmp(cur->value, "~", longer_len(cur->value, "~")) == 0)
	{
		free(cur->value);
		cur->value = get_env_value(mini->env, "HOME");
		if (!cur->value)
			return (ft_error(mini, NULL, strerror(errno)), 1);
		if (cur->value[0] == '\0')
			cur->value = ft_strdup("~");
	}
	if (cur->type == D_Q || cur->type == S_Q)
		cur->type = STRING;
	if (tok_list(cur->value, cur->type, new_list) == 1)
	{
		mini->token = *new_list;
		return (ft_error(mini, NULL, strerror(errno)), 1);
	}
	return (0);
}

static int	exp_env_var_utils(t_mini *mini, t_token	*cur, t_token **new_list)
{
	if ((cur->type == STRING || cur->type == D_Q || cur->type == S_Q)
		&& ft_strchr(cur->value, '$'))
	{
		if (expand_and_add(mini, cur, new_list) != 0)
		{
			mini->token = *new_list;
			return (ft_error(mini, NULL, strerror(errno)), 1);
		}
	}
	else
	{
		if (if_no_dollar(mini, cur, new_list) != 0)
			return (1);
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
		if (exp_env_var_utils(mini, cur, &new_list) != 0)
			return (1);
		free(cur->value);
		free (cur);
		cur = temp;
	}
	mini->token = new_list;
	return (0);
}
