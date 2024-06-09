/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:47:03 by sandra            #+#    #+#             */
/*   Updated: 2024/06/09 16:50:09 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redirs_text(t_mini *mini, t_token **cur, t_token **prev)
{
	if (*prev)
		(*prev)->next = *cur;
	else
		mini->token = *cur;
	*prev = *cur;
	*cur = (*cur)->next;
	if (*cur && (*cur)->type == TEXT)
	{
		(*prev)->next = *cur;
		*prev = *cur;
		*cur = (*cur)->next;
	}
}

static void	fill_cmd_table(t_token **cur, t_token *new, t_mini *mini)
{
	int	i;

	i = 0;
	while (*cur && ((*cur)->type == TEXT
			|| (*cur)->type == OPT || (*cur)->type == EMPTY))
	{
		if ((*cur)->type == EMPTY)
			new->cmd_tab[i] = ft_strdup("");
		else
			new->cmd_tab[i] = ft_strdup((*cur)->value);
		if (!new->cmd_tab[i])
			return (ft_error("Memory allocation error", mini));
		i++;
		*cur = (*cur)->next;
	}
	new->cmd_tab[i] = NULL;
}

static int	count_cmd_tokens(t_token *cur)
{
	t_token	*tmp;
	int		i;

	tmp = cur;
	i = 0;
	while (tmp && (tmp->type == TEXT || tmp->type == OPT || tmp->type == EMPTY))
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
		return (ft_error("Memory allocation error", mini));
	tok_count = count_cmd_tokens(*cur);
	new->cmd_tab = malloc((tok_count + 1) * sizeof(char *));
	if (!new->cmd_tab)
		return (ft_error("Memory allocation error", mini));
	fill_cmd_table(cur, new, mini);
	if (mini->error)
		return (clean_token_list(&new));
	if (*prev)
		(*prev)->next = new;
	else
		mini->token = new;
	new->next = *cur;
	*prev = new;
}

void	parse_commands(t_mini *mini)
{
	t_token	*cur;
	t_token	*prev;

	cur = mini->token;
	prev = NULL;
	printf("----entered parse command ----\n");
	while (cur)
	{
		printf("cur val: %s  type: %u\n", cur->value, cur->type);
		if (cur->type == TEXT || cur->type == OPT || cur->type == EMPTY)
		{
			create_cmd_tab(mini, &cur, &prev);
			if (mini->error)
				return ;
		}
		else if (cur->type == HEREDOC || cur->type == IN
			|| cur->type == OUT || cur->type == APPEND)
			handle_redirs_text(mini, &cur, &prev);
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}