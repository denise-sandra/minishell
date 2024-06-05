/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/06/05 15:32:12 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int error_if_triple(t_minishell *mini, t_type type)
{
	t_pretok	*list;
	
     list = mini->pretok;
	while (list)
	{
		if (list->type == type && list->next && list->next->next\
		&& list->next->type == type && list->next->next->type == type)
			return (1);
		list = list->next;
	}
     return (0);
}

int	check_syntax_errors(t_minishell *mini)
{
     
	if (error_if_double(mini, PIPE) == 1)
          return (1);
	if (error_if_triple(mini, IN) == 1)
          return (1);
     if (error_if_triple(mini, OUT) == 1)
          return (1);
	return (0);
}

//agregar si <> o ><