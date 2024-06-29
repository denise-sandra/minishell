/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_toks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:28:18 by sandra            #+#    #+#             */
/*   Updated: 2024/06/29 17:21:47 by sandra           ###   ########.fr       */
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
	order_out(mini);
	free(mini->order);
	mini->order = NULL;
	return (0);
}

// int	order_out(t_mini *mini)
// {
// 	t_token	*cur;
// 	t_token	*prev;
// 	t_token	*next;
// 	t_token	*out_lst;
// 	t_token *pipe_tail;
// 	t_token *print;
	

// 	cur = mini->token;
// 	prev = NULL;
// 	out_lst = NULL;
// 	pipe_tail = NULL;
// 	while (cur)
// 	{
// 		if (cur->next && cur->type == OUT && cur->next->type == STRING)
// 		{
// 			next = cur->next->next;
// 			cur->next->next = NULL;
// 			tok_addback(&out_lst, cur);
// 			if (prev)
// 				prev->next = next;
// 			else
// 				mini->token = next;
// 			cur = next;
// 		}
// 		else
// 		{
// 			if (cur->type == PIPE)
// 			{
// 				if (out_lst)
// 				{
// 					if (pipe_tail)
// 						tok_addback(&pipe_tail, out_lst);
// 					else
// 					{
// 						pipe_tail = cur;
// 						tok_addback(&out_lst, pipe_tail);
// 						cur = NULL; //deberia poner a null desde el pipe para que mini
// 									//sea desdel inicio al primer pipe, y despues atarlo a out_lst que ya tiene
// 									//pegado atras el resto del cmd. no entiendo porque no lo pone en nulo.
// 						print = mini->token;;
// 						while (print)
// 						{
// 							printf("2 %s\n", print->value);
// 							print = print->next;
// 						}
// 						tok_addback(&mini->token, out_lst);
// 						cur = pipe_tail;
// 					}	
// 					out_lst = NULL;
// 				}
// 			}
// 			prev = cur;
// 			cur = cur->next;
// 		}
// 	}
// 	if (out_lst)
// 	{
// 		if (pipe_tail)
// 			tok_addback(&pipe_tail, out_lst);
// 		else
// 			tok_addback(&mini->token, out_lst);
// 	}
// 	print = mini->token;
// 	while (print)
// 	{
// 		printf("2 %s\n", print->value);
// 		print = print->next;
// 	}
// 	return (0);
// }
