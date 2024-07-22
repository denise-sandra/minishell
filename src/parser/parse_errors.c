/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:52:44 by sandra            #+#    #+#             */
/*   Updated: 2024/07/22 10:45:48 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lec_utils(t_mini *mini, t_token *list, t_token *next)
{
	if (list->value && list->value[0] == '\\')
		ft_error(mini, "Syntax error: unsupported character `\\'", NULL);
	else if (list->type == HERE && (!next || (next && next->value[0] == '-')
			|| (next && next->type != LIM)))
		ft_error(mini, "Syntax error near token `<<'", NULL);
	else if ((list->type == IN || list->type == OUT) \
		&& next && next->type != STRING)
	{
		ft_error(mini, "Syntax error near redirection token", NULL);
	}
	else if (list->type == APP && (!next || (next && next->value[0] == '-')
			|| (next && next->type != STRING)))
		ft_error(mini, "Syntax error near token `>>'", NULL);
}

int	last_error_checks(t_mini *mini)
{
	t_token	*list;
	t_token	*next;

	list = mini->token;
	while (list)
	{
		next = list->next;
		lec_utils(mini, list, next);
		if (mini->error)
		{
			mini->exit_status = 2;
			return (1);
		}	
		list = list->next;
	}
	return (0);
}
