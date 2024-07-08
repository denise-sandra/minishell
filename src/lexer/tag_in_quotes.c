/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_in_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/06 14:27:08 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tag_inside_quotes(t_pretok *start, t_type quote_type)
{
	t_pretok	*current;

	current = start->next;
	while (current && current->type != quote_type)
	{
		current->type = CHAR;
		current = current->next;
	}
}

static void	remove_empty_quotes(t_pretok **start, t_pretok *end)
{
	t_pretok	*first_quote;

	first_quote = *start;
	first_quote->c = '\0';
	first_quote->type = EMPTY;
	first_quote->next = end->next;
	free(end);
}

t_pretok	*find_matching_quote(t_pretok *start, t_type quote_type)
{
	t_pretok	*current;
	int			count;

	current = start;
	count = 1;
	while (current && count > 0)
	{
		if (current->type == quote_type)
			count--;
		if (count == 0)
			break ;
		current = current->next;
	}
	return (current);
}

void	tag_in_quotes(t_mini *mini, t_pretok *close_quote)
{
	t_pretok	*current;

	current = mini->pretok;
	while (current)
	{
		if (current->type == S_Q || current->type == D_Q)
		{
			close_quote = find_matching_quote(current->next, current->type);
			if (!close_quote)
			{
				ft_error(mini, "Syntax error: unclosed quotes", NULL);
				break ;
			}
			if (current->next == close_quote)
				remove_empty_quotes(&current, close_quote);
			else
			{
				tag_inside_quotes(current, current->type);
				current = close_quote;
			}
		}
		if (current)
			current = current->next;
	}
}
