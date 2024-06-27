/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_toks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:28:18 by sandra            #+#    #+#             */
/*   Updated: 2024/06/27 13:41:59 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	adjust_position(t_mini *mini, t_token **cur, t_token **prev, t_token **first)
{
	t_token	*temp;

	if (*prev)
		(*prev)->next = (*cur)->next;
	(*cur)->next = *first;
	temp = *cur;
	if (*prev)
		*cur = (*prev)->next;
	else
		*cur = temp->next;
	if (!*prev)
		mini->token = temp;
	if (*prev == *first)
		*first = temp;
}


static void	handle_pipe(t_token **cur, t_token **prev, t_token **first)
{
	*first = NULL;
	*prev = *cur;
	*cur = (*cur)->next;
}

static void	handle_redirection(t_token **cur, t_token **prev, t_token **first, t_mini *ms)
{
	if (*first && (*prev != *first))
		adjust_position(ms, cur, prev, first);
	else
	{
		*prev = *cur;
		*cur = (*cur)->next;
	}
}

static void	handle_command(t_token **current, t_token **prev, t_token **first)
{
	if (!*first)
		*first = *current;
	*prev = *current;
	*current = (*current)->next;
}

void	order_token(t_mini *mini)
{
	t_token	*current;
	t_token	*prev;
	t_token	*first_nonredir;

	current = mini->token;
	prev = NULL;
	first_nonredir = NULL;
	while (current)
	{
		if (current->type == PIPE)
			handle_pipe(&current, &prev, &first_nonredir);
		else if (current->type == IN || current->type == OUT
			|| current->type == HERE || current->type == APP)
			handle_redirection(&current, &prev, &first_nonredir, mini);
		else
			handle_command(&current, &prev, &first_nonredir);
	}
}
