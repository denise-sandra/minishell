/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:14:20 by sandra            #+#    #+#             */
/*   Updated: 2024/06/29 17:27:27 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redirection(t_mini *mini, t_token **cur, t_token **next)
{
	*next = (*cur)->next->next;
	if (mini->order->prev)
		mini->order->prev->next = *next;
	else
		mini->token = *next;
	(*cur)->next->next = NULL;
	if (!mini->order->redir_head)
		mini->order->redir_head = *cur;
	else
	{
		mini->order->redir_tail = mini->order->redir_head;
		while (mini->order->redir_tail->next)
			mini->order->redir_tail = mini->order->redir_tail->next;
		mini->order->redir_tail->next = *cur;
	}
	*cur = *next;
}

static void	handle_pipe(t_mini *mini, t_token **cur)
{
	if (mini->order->redir_head && mini->order->cmd_tail)
	{
		mini->order->cmd_tail->next = mini->order->redir_head;
		mini->order->redir_tail = mini->order->redir_head;
		while (mini->order->redir_tail->next)
			mini->order->redir_tail = mini->order->redir_tail->next;
		mini->order->redir_tail->next = *cur;
		mini->order->redir_head = NULL;
	}
	mini->order->cmd_tail = *cur;
	*cur = (*cur)->next;
}

void	order_out(t_mini *mini)
{
	t_token	*cur;
	t_token	*next;

	cur = mini->token;
	while (cur)
	{
		next = cur->next;
		if ((cur->type == OUT || cur->type == APP)
			&& next && next->type == STRING)
			handle_redirection(mini, &cur, &next);
		else
		{
			if (cur->type == PIPE)
				handle_pipe(mini, &cur);
			else
			{
				mini->order->cmd_tail = cur;
				mini->order->prev = cur;
				cur = cur->next;
			}
		}
	}
	if (mini->order->redir_head && mini->order->cmd_tail)
		mini->order->cmd_tail->next = mini->order->redir_head;
}
