/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:22:03 by sandra            #+#    #+#             */
/*   Updated: 2024/06/12 09:11:53 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			expand_and_add(mini, cur, &new_list);
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
