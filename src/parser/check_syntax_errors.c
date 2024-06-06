/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/06/06 17:57:14 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int error_if_combination(t_minishell *mini, t_type type_a, t_type type_b)
{
     t_pretok	*list;

	list = mini->pretok;
	while (list)
	{

		if (list->type == type_a && list->next && list->next->type == type_b)
			return (1);
		list = list->next;
	}
	list = mini->pretok;
	while (list)
	{

		if (list->type == type_b && list->next && list->next->type == type_a)
			return (1);
		list = list->next;
	}
     return (0);
}

static int error_if_double(t_minishell *mini, t_type type)
{
     t_pretok	*list;

	list = mini->pretok;
	while (list)
	{

		if (list->type == type && list->next && list->next->type == type)
			return (1);
		list = list->next;
	}
     return (0);
}

static int error_append(t_minishell *mini)
{
	t_pretok	*list;

     list = mini->pretok;
	if (list && list->next && list->type == APPEND && list->next->type == APPEND)
	{
		if (list->next->next == NULL && list->next->next->c == '-'\
			&&  list->next->next->c == '>')
			return (1);
		if (list->next->next->c == 32 && list->next->next->next == NULL)
			return (1);
	}
     return (0);
}

static int error_heredoc(t_minishell *mini)
{
	t_pretok	*list;

     list = mini->pretok;
	if (list && list->next && list->type == HEREDOC && list->next->type == HEREDOC)
	{
		if (list->next->next == NULL && list->next->next->c == '*'\
			&& list->next->next->c == '-' && list->next->next->c == '/'\
			&&  list->next->next->c == '<')
			return (1);
		if (list->next->next->c == 32 && list->next->next->next == NULL)
			return (1);
	}
     return (0);
}

int	check_syntax_errors(t_minishell *mini)
{
     
	if (error_if_double(mini, PIPE) == 1)
          return (1);
	if (error_if_combination(mini, OUT, IN) == 1 || error_if_combination(mini, PIPE, OUT) == 1 \
	|| error_if_combination(mini, PIPE, IN) == 1)
          return (1);
	if (error_append(mini) == 1)
		return (1);
	if (error_heredoc(mini) == 1)
		return (1);
	return (0);
}
