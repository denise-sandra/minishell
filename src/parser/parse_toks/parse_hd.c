/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:04:54 by sandra            #+#    #+#             */
/*   Updated: 2024/07/26 15:23:26 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prep_lim(t_mini *mini, t_token	**cur, t_token	**prev)
{
	if ((*cur)->next && ((*cur)->next->type == STRING || \
			(*cur)->next->type == D_Q || (*cur)->next->type == S_Q))
	{
		join_tok(mini, cur, prev);
		(*cur)->type = LIM;
	}
	else
	{
		(*cur)->type = LIM;
		while ((*cur) && (*cur)->type != PIPE)
			(*cur) = (*cur)->next;
	}
}

static void	update_token(t_token **cur, t_token	**prev)
{
	if ((*cur)->type != WHITE)
	{
		*prev = (*cur);
		(*cur) = (*cur)->next;
	}
	else if ((*cur) && (*cur)->next && *prev && (*prev)->type == HERE)
		tok_delone(cur, prev);
	else if (*cur)
		*cur = (*cur)->next;
}

int	prep_heredoc(t_mini *mini)
{
	t_token	*prev;
	t_token	*cur;

	prev = NULL;
	cur = mini->token;
	while (cur)
	{
		if ((cur->type == STRING || cur->type == D_Q \
			|| cur->type == S_Q || cur->type == LIM)
			&& prev && prev->type == HERE)
			prep_lim(mini, &cur, &prev);
		else
			update_token(&cur, &prev);
		if (mini->error != 0)
			return (1);
	}
	return (0);
}
