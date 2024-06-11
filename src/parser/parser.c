/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/06/11 16:03:40 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tokenize_quotes(t_mini *ms, t_pretok **cur, t_token **lst, t_type q)
{
	char	*str;

	str = NULL;
	*cur = (*cur)->next;
	while (*cur && (*cur)->type != q)
	{
		str = ft_strjoin_char(str, (*cur)->c);
		if (!str)
			return (ft_error("Memory allocation error", ms));
		*cur = (*cur)->next;
	}
	if (*cur && (*cur)->type == q)
		*cur = (*cur)->next;
	if (str)
	{
		if (tok_list(str, q, lst) != 0)
			return (free(str), ft_error("Memory allocation error", ms));
		free(str);
	}
}

static void	tokenize_pipes(t_mini *mini, t_pretok **cur, t_token **list)
{
	if ((*cur)->type == PIPE)
	{
		if (!(*cur)->next)
			return (ft_error("Syntax error near unexpected token `|'", mini));
		if (tok_list("|", PIPE, list) != 0)
			return (ft_error("Memory allocation error", mini));
	}
	*cur = (*cur)->next;
}

static void	tokenize_strings(t_mini *mini, t_pretok **cur, t_token **list)
{
	char		*join;
	t_pretok	*prev;

	join = NULL;
	prev = NULL;
	while (*cur && ((*cur)->type == CHAR || (*cur)->type == EMPTY || (*cur)->type == OPT || (*cur)->type == D_Q || (*cur)->type == S_Q))
	{
		if ((*cur)->type == CHAR || (*cur)->type == OPT)
		{
			join = ft_strjoin_char(join, (*cur)->c);
			if (!join)
				return (ft_error("Memory allocation error", mini));
		}
		else if ((prev && prev->c == '=') && ((*cur)->type == D_Q || (*cur)->type == S_Q))
		{
			while ((*cur) && ((*cur)->type == CHAR || (*cur)->type == D_Q || (*cur)->type == S_Q))
			{
				printf("cur type in tok str: %u\n", (*cur)->type);
				join = ft_strjoin_char(join, (*cur)->c);
				if (!join)
					return (ft_error("Memory allocation error", mini));
				*cur = (*cur)->next;
			}
			printf("join: %s\n", join);
		}
		else if ((*cur)->type == EMPTY)
		{
			if (tok_list("", EMPTY, list) != 0)
				return (ft_error("Memory allocation error", mini));
		}
		if ((*cur))
		{
			prev = *cur;
			*cur = (*cur)->next;
		}
	}
	if (join)
	{
		if (tok_list(join, STRING, list) != 0)
			return (free(join), ft_error("Memory allocation error", mini));
		free(join);
	}
}

void	parser(t_mini *mini)
{
	t_pretok	*cur_pretok;

	cur_pretok = mini->pretok;
	while (cur_pretok)
	{
		if (cur_pretok->type == CHAR || cur_pretok->type == EMPTY
			|| cur_pretok->type == OPT)
			tokenize_strings(mini, &cur_pretok, &(mini->token));
		else if (cur_pretok->type == PIPE)
			tokenize_pipes(mini, &cur_pretok, &(mini->token));
		else if (cur_pretok->type == IN || cur_pretok->type == OUT)
			tokenize_redirs(mini, &cur_pretok, &(mini->token));
		else if (cur_pretok->type == D_Q || cur_pretok->type == S_Q)
			tokenize_quotes(mini, &cur_pretok, &(mini->token), cur_pretok->type);
		else
			cur_pretok = cur_pretok->next;
		if (mini->error != 0)
			return ;
	}
	clean_pretokens(mini);
	t_token *print = mini->token;
	while (print)
	{
		printf("tok: %s  type: %i\n", print->value, print->type);
		if (print->type == COMMAND)
		{
			for (int i = 0; print->cmd_tab[i]; i++)
				printf("cmd: %s\n", print->cmd_tab[i]);
		}
		print = print->next;
	}
	expand_env_vars(mini, mini->token);
	parse_commands(mini); //para despues, tener en cuenta que esto puede hacer un return despues de un error
	print = mini->token;
	while (print)
	{
		printf("new: %s  type: %i\n", print->value, print->type);
		if (print->type == COMMAND)
		{
			for (int i = 0; print->cmd_tab[i]; i++)
				printf("cmd: %s\n", print->cmd_tab[i]);
		}
		print = print->next;
	}
	// check_syntax_erros(mini);
}
