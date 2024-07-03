/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:14:20 by sandra            #+#    #+#             */
/*   Updated: 2024/07/02 10:43:10 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*handle_redirection(t_mini *mini, t_token **cur, t_token **next, t_token **out_lst)
{
	*next = (*cur)->next->next;
	if (mini->order->prev)
		mini->order->prev->next = *next;
	else
		mini->token = *next;
	(*cur)->next->next = NULL;
	tok_addback(out_lst, (*cur));
	*cur = *next;
	return (*out_lst);
}

static void	handle_pipe(t_mini *mini, t_token **cur, t_token **out_lst)
{
	if (out_lst && mini->order->cmd_tail)
		mini->order->cmd_tail->next =  *out_lst;
	tok_addback(&mini->token, *cur);
	mini->order->cmd_tail = *cur;
	*out_lst = NULL;
	mini->order->prev = *cur;
	*cur = (*cur)->next;
}

void	order_out(t_mini *mini)
{
	t_token	*cur;
	t_token	*next;
	t_token	*out_lst;

	out_lst = NULL;
	cur = mini->token;
	while (cur)
	{
		next = cur->next;
		if ((cur->type == OUT || cur->type == APP)
			&& next && next->type == STRING)
			out_lst = handle_redirection(mini, &cur, &next, &out_lst);
		else
		{
			if (cur->type == PIPE)
				handle_pipe(mini, &cur, &out_lst);
			else
			{
				mini->order->cmd_tail = cur;
				mini->order->prev = cur;
				cur = cur->next;
			}
		}
	}
	if (out_lst && mini->order->cmd_tail)
		mini->order->cmd_tail->next = out_lst;
}
