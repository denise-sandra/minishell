/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/06/05 15:44:10 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token *s_redir_t(t_minishell *mini)
{
	t_pretok *tmp;
	t_token   *new_node;
	char		*dir;

	if (mini->pretok->type == IN)
		dir = "<";
	else
		dir = ">";
	new_node = tok_new_node(dir);
	if (new_node == NULL)
		ft_error("Malloc creating token node", mini);
	tmp = mini->pretok->next;
	free(mini->pretok);
	mini->pretok = tmp;
	return (new_node);
}

static t_token *d_redir_t(t_minishell *mini)
{
	t_pretok *tmp;
	t_token   *new_node;
	char		*dir;

	if (mini->pretok->type == IN)
		dir = "<<";
	else
		dir = ">>";
	new_node = tok_new_node(dir);
	if (new_node == NULL)
		ft_error("Malloc creating token node", mini);
	tmp = mini->pretok->next->next;
	free(mini->pretok->next);
	free(mini->pretok);
	mini->pretok = tmp;
	return (new_node);
}

void	parser(t_minishell *mini)
{
	t_pretok *lexer;
	t_token   *token_list;
	t_token   *new_token;

	token_list = NULL;
	if (check_syntax_errors(mini) == 1)
		ft_error("Syntaxis error: invalid character", mini);
	lexer = mini->pretok;
	new_token = NULL;
	while (lexer)
	{
		if (lexer->next && ((lexer->type == IN && lexer->next->type == IN) \
			|| (lexer->type == OUT && lexer->next->type == OUT)))
			{
				new_token = d_redir_t(mini);
				lexer = mini->pretok;
			}	
		else if (lexer->type == IN || lexer->type == OUT)
		{
			new_token = s_redir_t(mini);
			lexer = mini->pretok;
		}	
		printf("token: %s\n", new_token->value);
		tok_addback(&token_list, new_token);
		if (lexer != NULL)
			lexer = lexer->next;
	}
	mini->token = token_list;
	clean_pretokens(mini);
}
