/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/07/22 13:43:20 by derjavec         ###   ########.fr       */
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
		if (!(*cur)->next || (*cur) == mini->pretok || (*cur)->next->type == PIPE)
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

static void	tokenize_slash(t_mini *mini, t_pretok **cur, t_token **list)
{
	char		*join;
	int			sq;
	int			dq;

	join = NULL;
	sq = 0;
	dq = 0;
	while (*cur && ((*cur)->type == CHAR || (*cur)->type == SLASH \
		|| (*cur)->type == S_Q || (*cur)->type == D_Q))
	{
		if ((*cur)->type == S_Q)
			sq++;
		if ((*cur)->type == D_Q)
			dq++;
		if ((*cur)->type == CHAR || (*cur)->type == SLASH ||\
		 ((*cur)->type == D_Q && sq % 2 != 0) || ((*cur)->type == S_Q && dq % 2 != 0))
		{
			join = ft_strjoin_char(join, (*cur)->c);
			if (!join)
				return (ft_error(mini, NULL, strerror(errno)));
		}
		*cur = (*cur)->next;
	}
	if (join)
	{
		if (tok_list(join, SLASH, list) != 0)
			return (free(join), ft_error(mini, NULL, strerror(errno)));
		free(join);
	}
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

int	prep_expand(t_mini *mini, t_token *token)
{
	t_token	*cur;
	t_token	*next;
	t_token	*new;
	int		res;
	int		i;
	char	*sub;

	cur = token;
	sub = NULL;
	while (cur)
	{
		res = ft_strchr_int(cur->value, '$');
		i = res + 1;
		next = cur->next;
		if ((cur->type == STRING)
			&& res >= 0)
		{
			while (cur->value[i])
			{
				if (!ft_isalnum(cur->value[i]) && cur->value[i] != '?')
				{
					sub = ft_substr(cur->value, i, (ft_strlen(cur->value) - i));
					if (!sub)
						return (ft_error(mini, NULL, strerror(errno)), -1);
					cur->value[i] = '\0';
					new = tok_new_node(sub, STRING);
					free(sub);
					if (!new)
						return (ft_error(mini, NULL, strerror(errno)), -1);
					cur->next = new;
					new->next = next;
					break ;
				}
				i++;
			}
		}
		cur = next;
	}
	return (0);
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
		else if (pretok->type == SLASH)
			tokenize_slash(mini, &pretok, &(mini->token));
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
	// t_token *print = mini->token;
	// while (print)
	// {
	// 	printf("1 tok %s  type: %i\n", print->value, print->type);
	// 	print = print->next;
	// }
	if (prep_heredoc(mini) != 0)
		return ;
	t_token *print = mini->token;
	while (print)
	{
		printf("1 tok %s  type: %i\n", print->value, print->type);
		print = print->next;
	}
	prep_expand(mini, mini->token);
	expand_env_vars(mini, mini->token);
	// print = mini->token;
	// while (print)
	// {
	// 	printf("expand : %s type %d\n", print->value, print->type);
	// 	print = print->next;
	// }
	if (mini->error != 0)
		return ;
	if(check_slash(mini) != 0)
		return ;
	if (check_white(mini) != 0)
		return ;
	if (order_tok_list(mini) == 1)
		return ;
	print = mini->token;
	while (print)
	{
		printf("token 2 : %s type %d\n", print->value, print->type);
		print = print->next;
	}
	if (parse_commands(mini) != 0)
		return ;
	last_error_checks(mini);
	print = mini->token;
	while (print)
	{
		printf("3 tok: %s  type: %i\n", print->value, print->type);
		if (print->type == COMMAND)
		{
			for (int i = 0; print->cmd_tab[i]; i++)
				printf("cmd: %s\n", print->cmd_tab[i]);
		}
		print = print->next;
	}
}
