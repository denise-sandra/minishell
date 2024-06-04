/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/04 18:15:41 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_dq(t_minishell *mini, t_pretok **in_dq)
{
	
}

static void	parse_quotes(t_minishell *mini)
{
	t_pretok	*tmp;
	// int			i;
	// char		*to_join;

	tmp = mini->pretok;
	// to_join = NULL;
	while (tmp)
	{
		if (tmp->type != D_Q && tmp->type != S_Q)
			tmp = tmp->next;
	}
	if (!tmp)
		return ;
	if (tmp->type == D_Q)
		parse_dq(mini, &tmp);
	else if (tmp->type == S_Q)
		parse_sq(mini);
}

int	lexer(char *input, t_minishell *mini)
{
	int			i;
	t_pretok	*node;

	i = 0;
	while (input[i])
	{
		// printf("input[%i]: %c\n", i, input[i]);
		node = pretok_new_node(input[i]);
		if (!node)
		{
			if (!mini->pretok)
				clean_pretokens(mini);
			return (0);
		}
		pretok_addback(&mini->pretok, node);
		i++;
	}
	parse_quotes(mini);
	// t_pretok *print = mini->pretok;
	// while (print)
	// {
	// 	printf("pretok val: %c  type: %i\n", print->c, print->type);
	// 	print = print->next;
	// }
	return (1);
}
