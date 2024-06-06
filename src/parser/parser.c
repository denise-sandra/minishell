/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/06/06 17:52:16 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_pretok	*simple_char(t_minishell *mini, char c, t_pretok *lexer)
{
	t_token	*new_node;
	char	s[2];

	s[0] = c;
	s[1] = '\0';
	new_node = tok_new_node(s, lexer->type);
	check_malloc_error(mini, new_node, "Malloc error", -1);
	tok_addback(&mini->token, new_node);
	return (lexer->next);
}

static t_pretok	*double_char(t_minishell *mini, t_pretok *lexer)
{
	t_token	*new_node;
	char	*s;

	if (lexer->type == IN)
		s = "<<";
	else
		s = ">>";
	new_node = tok_new_node(s, lexer->type);
	check_malloc_error(mini, new_node, "Malloc error", -1);
	tok_addback(&mini->token, new_node);
	return (lexer->next->next);
}

void	parser(t_minishell *mini)
{
	t_pretok	*lexer;

	if (check_syntax_errors(mini) == 1)
		ft_error("syntax error near unexpected token", mini);
	lexer = mini->pretok;
	while (lexer)
	{
		if (lexer->next && ((lexer->type == IN && lexer->next->type == IN) \
			|| (lexer->type == OUT && lexer->next->type == OUT)))
			lexer = double_char(mini, lexer);
		else if (lexer->type == IN || lexer->type == OUT || lexer->type == PIPE)
			lexer =simple_char(mini, lexer->c, lexer);
		else if (lexer->type == CHAR || lexer->type == ENV || lexer->type == EMPTY)
			lexer = type_join(mini, lexer);
		else if (lexer->type == OPT)
			lexer = opt_join(mini, lexer);
		else
			lexer = lexer->next;
	}
	clean_pretokens(mini);
	tag_token(mini);
}
