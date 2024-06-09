/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:04:54 by sandra            #+#    #+#             */
/*   Updated: 2024/06/09 14:58:23 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_double_redir(t_type type, t_pretok **cur)
{
	int	is_here;
	int	is_app;

	is_here = 0;
	is_app = 0;
	if (type == IN && (*cur)->next)
	{
		if ((*cur)->next->type == IN)
		{
			is_here = 1;
			return (is_here);
		}
	}
	else if (type == OUT && (*cur)->next)
	{
		if ((*cur)->next->type == OUT)
		{
			is_app = 1;
			return (is_app);
		}
	}
	return (0);
}

int	parse_double(t_type type, t_token **list, t_pretok **cur, t_mini *mini)
{
	if (type == IN)
	{
		if (tok_list("<<", HEREDOC, list) != 0)
		{
			ft_error("Memory allocation error", mini);
			return (1);
		}
	}
	else if (type == OUT)
	{
		if (tok_list(">>", APPEND, list) != 0)
		{
			ft_error("Memory allocation error", mini);
			return (1);
		}
	}
	*cur = (*cur)->next->next;
	return (0);
}

void	parse_redirs(t_mini *mini, t_pretok **cur, t_token **list)
{
	t_type	type;
	char	str[2];

	while (*cur)
	{
		type = (*cur)->type;
		str[0] = (*cur)->c;
		str[1] = '\0';
		// printf("Checking tok: %c, type: %u\n", (*cur)->c, (*cur)->type);
		if ((type == IN || type == OUT) && !(*cur)->next)
			return (ft_error("Syntax error unexpected token `newline'", mini));
		if ((type == IN && (*cur)->next->type != IN)
			|| (type == OUT && (*cur)->next->type != OUT))
		{
			if (tok_list(str, type, list) != 0)
				return (ft_error("Memory allocation error", mini));
			*cur = (*cur)->next;
		}
		else if (is_double_redir(type, cur))
		{
			if (parse_double(type, list, cur, mini) != 0)
				return ;
		}
		else
			break ;
	}
}
