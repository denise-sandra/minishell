/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:22:09 by sandra            #+#    #+#             */
/*   Updated: 2024/07/30 11:09:10 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	double_red(t_type type, t_token **list, t_pretok **cur, t_mini *ms)
{
	if (type == IN)
	{
		if (tok_list("<<", HERE, list) != 0)
			return (ft_error(ms, NULL, strerror(errno)), 1);
	}
	else if (type == OUT)
	{
		if (tok_list(">>", APP, list) != 0)
			return (ft_error(ms, NULL, strerror(errno)), 1);
	}
	*cur = (*cur)->next->next;
	return (0);
}

static int	is_double_redir(t_type type, t_pretok **cur)
{
	if (type == IN && (*cur)->next)
	{
		if ((*cur)->next->type == IN)
			return (1);
	}
	else if (type == OUT && (*cur)->next)
	{
		if ((*cur)->next->type == OUT)
			return (1);
	}
	return (0);
}

void	tokenize_redirs(t_mini *ms, t_pretok **cur, t_token **list)
{
	t_type	type;
	char	str[2];

	while (*cur)
	{
		type = (*cur)->type;
		str[0] = (*cur)->c;
		str[1] = '\0';
		if ((type == IN || type == OUT) && !(*cur)->next)
		{
			ms->exit_status = 2;
			return (ft_error(ms, "Syntax error near token `newline'", NULL));
		}
		if ((type == IN && (*cur)->next->type != IN)
			|| (type == OUT && (*cur)->next->type != OUT))
		{
			if (tok_list(str, type, list) != 0)
				return (ft_error(ms, NULL, strerror(errno)));
			*cur = (*cur)->next;
		}
		else if (is_double_redir(type, cur))
		{
			if (double_red(type, list, cur, ms) != 0)
				return ;
		}
		else
			break ;
	}
}
