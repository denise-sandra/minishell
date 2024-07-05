/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/07/05 15:48:22 by skanna           ###   ########.fr       */
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
			return (ft_error(ms, NULL, strerror(errno)));
		*cur = (*cur)->next;
	}
	if (*cur && (*cur)->type == q)
		*cur = (*cur)->next;
	if (str)
	{
		if (tok_list(str, q, lst) != 0)
			return (ft_error(ms, NULL, strerror(errno)));
		free(str);
	}
}

static void	tokenize_pipes_n_empty(t_mini *mini, t_pretok **cur, t_token **list)
{
	if ((*cur)->type == PIPE)
	{
		if (!(*cur)->next)
		{
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

static char	*tok_str_help(t_mini *ms, t_pretok **cur, char *s, t_pretok **prev)
{
	if ((*cur)->type == CHAR || (*cur)->type == OPT)
	{
		s = ft_strjoin_char(s, (*cur)->c);
		if (!s)
			return (ft_error(ms, NULL, strerror(errno)), NULL);
	}
	else if ((*prev && (*prev)->c == '=') && ((*cur)->type == D_Q
			|| (*cur)->type == S_Q))
	{
		while ((*cur) && ((*cur)->type == CHAR
				|| (*cur)->type == D_Q || (*cur)->type == S_Q))
		{
			s = ft_strjoin_char(s, (*cur)->c);
			if (!(*s))
				return (ft_error(ms, NULL, strerror(errno)), NULL);
			*cur = (*cur)->next;
		}
	}
	return (s);
}

static void	tokenize_strings(t_mini *mini, t_pretok **cur, t_token **list)
{
	char		*join;
	t_pretok	*prev;

	join = NULL;
	prev = NULL;
	while (*cur && ((*cur)->type == CHAR || (*cur)->type == EMPTY
			|| (*cur)->type == OPT))
	{
		join = tok_str_help(mini, cur, join, &prev);
		if (!join)
			return ;
		if (*cur)
		{
			prev = *cur;
			*cur = (*cur)->next;
		}
	}
	if (join)
	{
		if (tok_list(join, STRING, list) != 0)
			return (free(join), ft_error(mini, NULL, strerror(errno)));
		free(join);
	}
}

static void check_white(t_mini *mini)
{
	t_token *tmp;
	t_token *prev;
	t_token	*new;
	char	*new_token;

	tmp = mini->token;
	prev = NULL;
	while (tmp)
	{
		if ((tmp->type == STRING || tmp->type == D_Q || tmp->type == S_Q)
			&& tmp->next && (tmp->next->type == STRING || \
			tmp->next->type == D_Q || tmp->next->type == S_Q))
		{
			new_token = ft_strjoin_free(tmp->value, tmp->next->value);
			if (!new_token)
				return (ft_error(mini, NULL, strerror(errno)));
			new = tok_new_node(new_token, STRING);
			free(new_token);
			if (!new)
				return (ft_error(mini, NULL, strerror(errno)));
			new->next = tmp->next->next;
			free(tmp->next);
			free(tmp);
			tmp = new;
			if (prev)
				prev->next = new;
			else
				mini->token = new;
		}
		else if (tmp->type == WHITE)
		{
			if (prev)
			{
				prev->next = tmp->next;
				free(tmp->value);
				free(tmp);
				tmp = prev->next;
			}
			else
			{
				mini->token = tmp->next;
				free(tmp->value);
				free(tmp);
				tmp = mini->token;
			}
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}


void	parser(t_mini *mini)
{
	t_pretok	*pretok;

	pretok = mini->pretok;
	while (pretok)
	{
		if (pretok->c == '$' && pretok->next && (pretok->next->type == D_Q || pretok->next->type == S_Q))
			pretok = pretok->next;
		else if (pretok->type == CHAR || pretok->type == OPT)
			tokenize_strings(mini, &pretok, &(mini->token));
		else if (pretok->type == PIPE || pretok->type == EMPTY)
			tokenize_pipes_n_empty(mini, &pretok, &(mini->token));
		else if (pretok->type == IN || pretok->type == OUT)
			tokenize_redirs(mini, &pretok, &(mini->token));
		else if (pretok->type == D_Q || pretok->type == S_Q)
			tokenize_quotes(mini, &pretok, &(mini->token), pretok->type);
		else if (pretok->type == WHITE)
		{
			if (tok_list(" ", WHITE, &(mini->token)) != 0)
				return (ft_error(mini, NULL, strerror(errno)));
			pretok = pretok->next;
		}
		else
			pretok = pretok->next;
		if (mini->error != 0)
			return ;
	}
	clean_pretokens(mini);
	
	// while (print)
	// {
	// 	printf("1 tok %s  type: %i\n", print->value, print->type);
	// 	print = print->next;
	// }
	prep_heredoc(mini);
	expand_env_vars(mini, mini->token);
	check_white(mini);
	if (order_tok_list(mini) == 1)
		return ;
	// print = mini->token;
	// while (print)
	// {
	// 	printf("order : %s type %d\n", print->value, print->type);
	// 	print = print->next;
	// }
	parse_commands(mini);
	last_error_checks(mini);
	// t_token *print = mini->token;
	// while (print)
	// {
	// 	printf("2 tok: %s  type: %i\n", print->value, print->type);
	// 	if (print->type == COMMAND)
	// 	{
	// 		for (int i = 0; print->cmd_tab[i]; i++)
	// 			printf("cmd: %s\n", print->cmd_tab[i]);
	// 	}
	// 	print = print->next;
	// }
}
