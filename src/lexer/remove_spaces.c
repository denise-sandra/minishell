/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/05 03:25:23 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_end_spaces(t_minishell *mini)
{
	t_pretok	*current;
	t_pretok	*prev;

	current = mini->pretok;
	prev = NULL;
	while (current && current->next)
	{
		prev = current;
		current = current->next;
	}
	if (current && current->type == WHITE)
	{
		if (prev)
			prev->next = NULL;
		else
			mini->pretok = NULL;
		free(current);
	}
}

static void	remove_init_spaces(t_minishell *mini)
{
	t_pretok	*temp;

	while (mini->pretok && mini->pretok->type == WHITE)
	{
		temp = mini->pretok;
		mini->pretok = mini->pretok->next;
		free(temp);
	}
}

static void	remove_consec_spaces(t_pretok *current)
{
	t_pretok	*temp;

	while (current->next && current->next->type == WHITE)
	{
		temp = current->next;
		current->next = temp->next;
		free(temp);
	}
}

void	remove_spaces(t_minishell *mini)
{
	t_pretok	*current;
	int			inside_quotes;

	inside_quotes = 0;
	remove_init_spaces(mini);
	current = mini->pretok;
	while (current)
	{
		if (current->type == S_Q || current->type == D_Q)
			inside_quotes++;
		if (current->type == WHITE && inside_quotes % 2 == 0)
			remove_consec_spaces(current);
		current = current->next;
	}
	remove_end_spaces(mini);
}
