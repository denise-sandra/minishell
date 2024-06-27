/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_toks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:28:18 by sandra            #+#    #+#             */
/*   Updated: 2024/06/27 18:03:24 by derjavec         ###   ########.fr       */
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

// int	order_out(t_mini *mini)
// {
// 	t_token	*cur;
// 	t_token	*prev;
// 	t_token	*out_lst;

// 	cur = mini->token;
// 	prev = NULL;
// 	out_lst = NULL;
// 	while (cur)
// 	{
// 		printf("cur :%s\n", cur->value);
// 		if (cur->next && cur->type == OUT && cur->next->type == STRING)
// 		{
// 			tok_addback(&out_lst, cur);
// 			tok_addback(&out_lst, cur->next);
// 			printf("out_lst :%s\n", out_lst->value);
// 			if (prev)
// 				prev->next = cur->next->next;
// 			else
// 				mini->token = cur->next->next;
// 			cur = cur->next->next;
// 		}
// 		else
// 		{
// 			prev = cur;
// 			cur = cur->next;
// 		}
// 	}
// 	if (out_lst)
// 		cur = out_lst;
// 	return (0);
// }

int	order_tok(t_mini *mini)
{
	if (init_order_struct(mini) == 1)
		return (1) ;
	order_in(mini);
	connect_tok(mini);
	//order_out(mini);
	return (0);
}
