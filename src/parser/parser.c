/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/07/25 15:17:33 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dollar_found(t_mini *mini, t_token **cur, t_token **next, int i)
{
	t_token	*new;
	char	*sub;

	sub = NULL;
	while ((*cur)->value[i])
	{
		if (!ft_isalnum((*cur)->value[i]) && (*cur)->value[i] != '?')
		{
			sub = ft_substr((*cur)->value, i, (ft_strlen((*cur)->value) - i));
			if (!sub)
				return (ft_error(mini, NULL, strerror(errno)), -1);
			(*cur)->value[i] = '\0';
			new = tok_new_node(sub, STRING);
			free(sub);
			if (!new)
				return (ft_error(mini, NULL, strerror(errno)), -1);
			(*cur)->next = new;
			new->next = *next;
			break ;
		}
		i++;
	}
	return (0);
}

int	prep_expand(t_mini *mini, t_token *token)
{
	t_token	*cur;
	t_token	*next;
	int		res;

	cur = token;
	while (cur)
	{
		next = cur->next;
		if (cur->value != NULL && cur->value[0] != '\0')
		{
			res = ft_strchr_int(cur->value, '$');
			if ((cur->type == STRING) && res >= 0)
			{
				if (dollar_found(mini, &cur, &next, res + 1) < 0)
					return (-1);
			}
		}
		cur = next;
	}
	return (0);
}

static void    tokenize(t_mini *mini, t_pretok **pretok)
{
	if ((*pretok)->c == '$' && (*pretok)->next && \
		((*pretok)->next->type == D_Q || (*pretok)->next->type == S_Q))
		(*pretok) = (*pretok)->next;
	else if ((*pretok)->type == CHAR || (*pretok)->type == OPT)
		tokenize_strings(mini, pretok, &(mini->token));
	else if ((*pretok)->type == SLASH)
		tokenize_slash(mini, pretok, &(mini->token));
	else if ((*pretok)->type == PIPE || (*pretok)->type == EMPTY)
		tokenize_pipes_n_empty(mini, pretok, &(mini->token));
	else if ((*pretok)->type == IN || (*pretok)->type == OUT)
		tokenize_redirs(mini, pretok, &(mini->token));
	else if ((*pretok)->type == D_Q || (*pretok)->type == S_Q)
		tokenize_quotes(mini, pretok, &(mini->token), (*pretok)->type);
	else if ((*pretok)->type == WHITE)
	{
		if (tok_list(" ", WHITE, &(mini->token)) != 0)
			return (ft_error(mini, NULL, strerror(errno)));
		(*pretok) = (*pretok)->next;
	}
	else
		(*pretok) = (*pretok)->next;
}

void	parser(t_mini *mini)
{
	t_pretok	*pretok;

	pretok = mini->pretok;
	while (pretok)
	{
		tokenize(mini, &pretok);
		if (mini->error != 0)
			return ;
	}
	clean_pretokens(mini);
	if (prep_heredoc(mini) != 0)
		return ;
	prep_expand(mini, mini->token);
	expand_env_vars(mini, mini->token);
	if (mini->error != 0)
		return ;
	if (check_slash(mini) != 0)
		return ;
	if (check_white(mini) != 0)
		return ;
	if (order_tok_list(mini) == 1)
		return ;
	if (parse_commands(mini) != 0)
		return ;
	last_error_checks(mini);
}
