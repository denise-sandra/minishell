/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/06/10 16:41:10 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_pretok	*simple_char(t_minishell *mini, char c, t_pretok *lexer, t_type prev)
{
	t_token	*new_node;
	char	s[2];

	s[0] = c;
	s[1] = '\0';
	new_node = tok_new_node(s, lexer->type, prev);
	check_malloc_error(mini, new_node, "Malloc error", -1);
	tok_addback(&mini->token, new_node);
	return (lexer->next);
}

static t_pretok	*double_char(t_minishell *mini, t_pretok *lexer, t_type prev)
{
	t_token	*new_node;
	t_type	type;
	char	*s;

	if (lexer->type == IN)
	{
		s = "<<";
		type = HEREDOC;
	}
	else
	{
		s = ">>";
		type = APPEND;
	}	
	new_node = tok_new_node(s, type, prev);
	check_malloc_error(mini, new_node, "Malloc error", -1);
	tok_addback(&mini->token, new_node);
	return (lexer->next->next);
}

static	t_pretok	*empty_node(t_minishell *mini, t_pretok *lexer, t_type prev)
{
	t_token	*new_node;

	new_node = tok_new_node("", lexer->type, prev);
	check_malloc_error(mini, new_node, "Malloc error", -1);
	tok_addback(&mini->token, new_node);
	return (lexer->next);
}

void	parser(t_minishell *mini)
{
	t_pretok	*lexer;
	t_type		current;
	t_type		prev;

	if (check_syntax_errors(mini) == 1)
		ft_error("syntax error near unexpected token", mini);
	lexer = mini->pretok;
	prev = EMPTY;
	while (lexer)
	{
		current = lexer->type;
		if (lexer->next && ((lexer->type == IN && lexer->next->type == IN) \
			|| (lexer->type == OUT && lexer->next->type == OUT)))
			lexer = double_char(mini, lexer, prev);
		else if (lexer->type == IN || lexer->type == OUT || lexer->type == PIPE)
			lexer = simple_char(mini, lexer->c, lexer, prev);
		else if (lexer->type == CHAR || lexer->type == ENV)
			lexer = type_join(mini, lexer, prev);
		else if (lexer->type == OPT)
			lexer = opt_join(mini, lexer, prev);
		else if (lexer->type == EMPTY)
			lexer = empty_node(mini, lexer, prev);
		else
			lexer = lexer->next;
		prev = current;
	}
	clean_pretokens(mini);
	tag_token(mini);
	parse_commands(mini);
	t_token *tmp = mini->token;
	while (tmp)
	{
		printf("tok: %s  type: %i\n", tmp->value, tmp->type);
		int i = 0;
		if (tmp->tab && tmp->tab[i])
		{
			while (tmp->tab[i])
			{	printf("tab[%i]: %s\n", i, tmp->tab[i]);
				i++;
			}
		}
		tmp = tmp->next;
	}
}
