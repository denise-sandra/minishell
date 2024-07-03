/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_toks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:28:18 by sandra            #+#    #+#             */
/*   Updated: 2024/07/03 14:11:11 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	connect_tok(t_mini *mini)
{
	t_order	*order;

	order = mini->order;
	if (order->redir_tail)
	{
		order->redir_tail->next = order->cmd_head;
		if (order->cmd_tail)
			order->cmd_tail->next = NULL;
		if (order->prev)
			order->prev->next = order->redir_head;
		else
			mini->token = order->redir_head;
	}
	else if (order->cmd_tail)
	{
		if (order->prev)
			order->prev->next = order->cmd_head;
		else
			mini->token = order->cmd_head;
	}
}

static int	init_order_struct(t_mini *mini)
{

	mini->order = malloc(sizeof(t_order));
	if (!mini->order)
		return (ft_error(mini, NULL, strerror(errno)), 1);
	mini->order->prev = NULL;
	mini->order->redir_head = NULL;
	mini->order->redir_tail = NULL;
	mini->order->cmd_head = NULL;
	mini->order->cmd_tail = NULL;
	return (0);
}

int	order_tok(t_mini *mini)
{
	if (init_order_struct(mini) == 1)
		return (1);
	order_in(mini);
	connect_tok(mini);
	ft_bzero(mini->order, sizeof(t_order));
	order_out(mini, mini->token);
	free(mini->order);
	mini->order = NULL;
	return (0);
}
