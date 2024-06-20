/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:52:44 by sandra            #+#    #+#             */
/*   Updated: 2024/06/20 14:49:05 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_error_checks(t_mini *mini)
{
	t_token	*list;
	t_token	*next;

	list = mini->token;
	while (list)
	{
		next = list->next;
		if (list->value && list->value[0] == '\\')
			ft_error(mini, "Syntax error: unsupported character `\\'", NULL);
		else if ((list->type == PIPE && next)
			&& (next->type != COMMAND && next->type != IN))
			ft_error(mini, "Syntax error near unexpected token `|'", NULL);
		else if (list->type == HERE && (!next || (next && next->value[0] == '-')
				|| (next && next->type != STRING)))
			ft_error(mini, "Syntax error near token `<<'", NULL);
		else if (list->type == APP && (!next || (next && next->value[0] == '-')
				|| (next && next->type != STRING)))
			ft_error(mini, "Syntax error near token `>>'", NULL);
		if (mini->error)
			return (1);
		list = list->next;
	}
	return (0);
}
