/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_white_and_slash.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/07/26 15:26:26 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	erase_white_tok(t_mini *mini, t_token **tmp, t_token **prev)
{
	if (*prev)
	{
		(*prev)->next = (*tmp)->next;
		free((*tmp)->value);
		free(*tmp);
		*tmp = (*prev)->next;
	}
	else
	{
		mini->token = (*tmp)->next;
		free((*tmp)->value);
		free(*tmp);
		*tmp = mini->token;
	}
}

int	check_white(t_mini *mini)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = mini->token;
	prev = NULL;
	while (tmp)
	{
		if ((tmp->type == STRING || tmp->type == D_Q || tmp->type == S_Q)
			&& tmp->next && (tmp->next->type == STRING || \
			tmp->next->type == D_Q || tmp->next->type == S_Q))
			join_tok(mini, &tmp, &prev);
		else if (tmp->type == WHITE || (tmp->type == EMPTY && !prev \
			&& tmp->next && tmp->next->type != WHITE))
			erase_white_tok(mini, &tmp, &prev);
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (mini->error != 0)
			return (1);
	}
	return (0);
}

int	check_slash(t_mini *mini)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = mini->token;
	prev = NULL;
	while (tmp)
	{
		if ((tmp->type == STRING || tmp->type == D_Q || tmp->type == S_Q)
			&& tmp->next && tmp->next->type == SLASH)
			join_tok(mini, &tmp, &prev);
		else if (tmp->type == SLASH)
		{
			tmp->type = STRING;
			tmp = tmp->next;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (mini->error != 0)
			return (1);
	}
	return (0);
}
