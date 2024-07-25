/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/07/25 14:46:30 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_pipes_n_empty(t_mini *mini, t_pretok **cur, t_token **list)
{
	if ((*cur)->type == PIPE)
	{
		if (!(*cur)->next || (*cur) == mini->pretok \
			|| (*cur)->next->type == PIPE)
		{
			mini->exit_status = 258;
			ft_error(mini, "Syntax error near unexpected token `|'", NULL);
			return ;
		}
		if (tok_list("|", PIPE, list) != 0)
			return (ft_error(mini, NULL, strerror(errno)));
	}
	else if ((*cur)->type == EMPTY)
	{
		if (tok_list("", EMPTY, list) != 0)
			return (ft_error(mini, NULL, strerror(errno)));
	}
	*cur = (*cur)->next;
}

static char	*tok_slash_utils(t_pretok **cur, int *sq, int *dq, char *join)
{
	if ((*cur)->type == S_Q)
		(*sq)++;
	if ((*cur)->type == D_Q)
		(*dq)++;
	if ((*cur)->type == CHAR || (*cur)->type == SLASH || \
		((*cur)->type == D_Q && *sq % 2 != 0) || \
		((*cur)->type == S_Q && *dq % 2 != 0))
	{
		join = ft_strjoin_char(join, (*cur)->c);
		if (!join)
			return (NULL);
	}
	return (join);
}

void	tokenize_slash(t_mini *mini, t_pretok **cur, t_token **list)
{
	char		*join;
	int			sq;
	int			dq;

	sq = 0;
	dq = 0;
	join = NULL;
	while (*cur && ((*cur)->type == CHAR || (*cur)->type == SLASH \
		|| (*cur)->type == S_Q || (*cur)->type == D_Q))
	{
		join = tok_slash_utils(cur, &sq, &dq, join);
		if (!join)
			return (ft_error(mini, NULL, strerror(errno)));
		*cur = (*cur)->next;
	}
	if (join)
	{
		if (tok_list(join, SLASH, list) != 0)
			return (free(join), ft_error(mini, NULL, strerror(errno)));
		free(join);
	}
}
