/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:22:03 by sandra            #+#    #+#             */
/*   Updated: 2024/06/20 14:47:39 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_exp(t_mini *mini, t_token *cur)
{
	char	*tmp;

	tmp = ft_strchr(cur->value, '$');
	if (ft_isdigit(tmp[1]) == 1 && ft_isdigit(tmp[2]) == 1)
	{
		mini->exit_status = 1;
		return (ft_error(mini, "Syntax error: unsupported character", NULL), 1);
	}
	return (0);
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
