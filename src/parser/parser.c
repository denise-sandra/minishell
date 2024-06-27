/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/06/27 15:48:05 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tokenize_quotes(t_mini *ms, t_pretok **cur, t_token **lst, t_type q)
{
	char	*str;

	str = NULL;
	*cur = (*cur)->next;
	while (*cur && (*cur)->type != WHITE)
	{
		str = ft_strjoin_char(str, (*cur)->c);
		if (!str)
			return (ft_error(ms, NULL, strerror(errno)));
		*cur = (*cur)->next;
		while (*cur && (*cur)->type == q)
			*cur = (*cur)->next;
	}
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

static void	tok_str_help(t_mini *ms, t_pretok **cur, char **s, t_pretok **prev)
{
	if ((*cur)->type == CHAR || (*cur)->type == OPT)
	{
		*s = ft_strjoin_char(*s, (*cur)->c);
		if (!(*s))
			return (ft_error(ms, NULL, strerror(errno)));
	}
	else if ((*prev && (*prev)->c == '=') && ((*cur)->type == D_Q
			|| (*cur)->type == S_Q))
	{
		while ((*cur) && ((*cur)->type == CHAR
				|| (*cur)->type == D_Q || (*cur)->type == S_Q))
		{
			*s = ft_strjoin_char(*s, (*cur)->c);
			if (!(*s))
				return (ft_error(ms, NULL, strerror(errno)));
			*cur = (*cur)->next;
		}
	}
}

static void	tokenize_strings(t_mini *mini, t_pretok **cur, t_token **list)
{
	char		*join;
	t_pretok	*prev;

	join = NULL;
	prev = NULL;
	while (*cur && ((*cur)->type == CHAR || (*cur)->type == EMPTY
			|| (*cur)->type == OPT || (*cur)->type == D_Q
			|| (*cur)->type == S_Q))
	{
		tok_str_help(mini, cur, &join, &prev);
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

void	parser(t_mini *mini)
{
	t_pretok	*pretok;

	pretok = mini->pretok;
	while (pretok)
	{
		if (pretok->type == CHAR || pretok->type == OPT)
			tokenize_strings(mini, &pretok, &(mini->token));
		else if (pretok->type == PIPE || pretok->type == EMPTY)
			tokenize_pipes_n_empty(mini, &pretok, &(mini->token));
		else if (pretok->type == IN || pretok->type == OUT)
			tokenize_redirs(mini, &pretok, &(mini->token));
		else if (pretok->type == D_Q || pretok->type == S_Q)
			tokenize_quotes(mini, &pretok, &(mini->token), pretok->type);
		else
			pretok = pretok->next;
		if (mini->error != 0)
			return ;
	}
	clean_pretokens(mini);
	expand_env_vars(mini, mini->token);
	t_token *print = mini->token;
	while (print)
	{
		printf("1new: %s  type: %i\n", print->value, print->type);
		if (print->type == COMMAND)
		{
			for (int i = 0; print->cmd_tab[i]; i++)
				printf("cmd: %s\n", print->cmd_tab[i]);
		}
		print = print->next;
	}
	if (order_in(mini) == 1)
		return ;
	parse_commands(mini);
	print = mini->token;
	while (print)
	{
		printf("2new: %s  type: %i\n", print->value, print->type);
		if (print->type == COMMAND)
		{
			for (int i = 0; print->cmd_tab[i]; i++)
				printf("cmd: %s\n", print->cmd_tab[i]);
		}
		print = print->next;
	}
	last_error_checks(mini);
}
