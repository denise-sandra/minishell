/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:28:18 by sandra            #+#    #+#             */
/*   Updated: 2024/06/29 17:27:23 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_pipes_utils(t_mini *mini, t_order *order)
{
	order->redir_tail->next = order->cmd_head;
	if (order->cmd_tail)
		order->cmd_tail->next = NULL;
	if (order->prev)
		order->prev->next = order->redir_head;
	else
		mini->token = order->redir_head;
	if (order->cmd_tail)
		order->prev = order->cmd_tail;
	else
		order->prev = order->redir_tail;
}

static void	handle_pipes(t_mini *mini, t_token	**cur, t_token	**next)
{
	t_order	*order;

	order = mini->order;
	if (order->redir_tail)
		handle_pipes_utils(mini, order);
	else if (order->cmd_tail)
	{
		if (order->prev)
			order->prev->next = order->cmd_head;
		else
			mini->token = order->cmd_head;
		order->prev = order->cmd_tail;
	}
	if (order->prev)
		order->prev->next = *cur;
	order->prev = *cur;
	order->redir_head = NULL;
	order->redir_tail = NULL;
	order->cmd_head = NULL;
	order->cmd_tail = NULL;
	*cur = *next;
}

static void	handle_infiles(t_mini *mini, t_token **cur, t_token **next)
{
	t_order	*order;

	order = mini->order;
	if (order->redir_tail)
	{
		order->redir_tail->next = *cur;
		order->redir_tail = *cur;
	}
	else
	{
		order->redir_head = *cur;
		order->redir_tail = *cur;
	}
	if (*next && (*next)->type == STRING)
	{
		order->redir_tail->next = *next;
		order->redir_tail = *next;
		*cur = (*next)->next;
	}
	else
		*cur = *next;
}

static void	handle_string(t_mini *mini, t_token **cur, t_token **next)
{
	t_order	*order;

	order = mini->order;
	if (order->cmd_tail)
	{
		order->cmd_tail->next = *cur;
		order->cmd_tail = *cur;
	}
	else
	{
		order->cmd_head = *cur;
		order->cmd_tail = *cur;
	}
	(*cur)->next = NULL;
	*cur = *next;
}

void	order_in(t_mini *mini)
{
	t_token	*cur;
	t_token	*next;

	cur = mini->token;
	while (cur)
	{
		next = cur->next;
		if (cur->type == PIPE)
			handle_pipes(mini, &cur, &next);
		else if (cur->type == IN || cur->type == HERE)
			handle_infiles(mini, &cur, &next);
		else
			handle_string(mini, &cur, &next);
	}
}
