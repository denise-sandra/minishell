/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:47:03 by sandra            #+#    #+#             */
/*   Updated: 2024/07/08 16:18:42 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redirs_next(t_mini *mini, t_token **cur, t_token **prev)
{
	if (*prev)
		(*prev)->next = *cur;
	else
		mini->token = *cur;
	*prev = *cur;
	*cur = (*cur)->next;
	if (*cur && (*cur)->type == STRING)
	{
		(*prev)->next = *cur;
		*prev = *cur;
		*cur = (*cur)->next;
	}
}

static int	fill_cmd_table(t_token **cur, t_token *new)
{
	int		i;
	t_token	*tmp;

	i = 0;
	while (*cur && ((*cur)->type == STRING
			|| (*cur)->type == OPT || (*cur)->type == EMPTY))
	{
		if ((*cur)->type == EMPTY)
			new->cmd_tab[i] = ft_strdup("");
		else
			new->cmd_tab[i] = ft_strdup((*cur)->value);
		if (!new->cmd_tab[i])
			return (-1);
		i++;
		tmp = (*cur)->next;
		free((*cur)->value);
		free(*(cur));
		*cur = tmp;
	}
	new->cmd_tab[i] = NULL;
	return (0);
}

static int	count_cmd_tokens(t_token *tmp)
{
	int		i;

	i = 0;
	while (tmp && (tmp->type == STRING
			|| tmp->type == OPT || tmp->type == EMPTY))
	{
		i++;
		tmp = tmp->next;
	}
	while (tmp && (tmp->type == IN || tmp->type == OUT \
			|| tmp->type == HERE || tmp->type == APP))
	{
		if (tmp->next && tmp->next->next)
			tmp = tmp->next->next;
		else
			tmp = tmp->next;
	}
	while (tmp && (tmp->type == STRING
			|| tmp->type == OPT || tmp->type == EMPTY))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	create_cmd_tab(t_mini *mini, t_token **cur, t_token **prev)
{
	t_token	*new;
	int		tok_count;

	new = tok_new_node("", COMMAND);
	if (!new)
		return (ft_error(mini, NULL, strerror(errno)));
	tok_count = count_cmd_tokens(*cur);
	new->cmd_tab = malloc((tok_count + 1) * sizeof(char *));
	if (!new->cmd_tab)
		return (ft_error(mini, NULL, strerror(errno)));
	if (fill_cmd_table(cur, new) != 0)
	{
		mini->token = new;
		ft_error(mini, NULL, strerror(errno));
		return ;
	}
	if (*prev)
		(*prev)->next = new;
	else
		mini->token = new;
	new->next = *cur;
	*prev = new;
}

int	parse_commands(t_mini *mini)
{
	t_token	*cur;
	t_token	*prev;

	cur = mini->token;
	prev = NULL;
	while (cur)
	{
		if (cur->type == STRING || cur->type == OPT || cur->type == EMPTY)
		{
			create_cmd_tab(mini, &cur, &prev);
			if (mini->error)
				return (1);
		}
		else if (cur->type == HERE || cur->type == IN
			|| cur->type == OUT || cur->type == APP)
			handle_redirs_next(mini, &cur, &prev);
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	return (0);
}
