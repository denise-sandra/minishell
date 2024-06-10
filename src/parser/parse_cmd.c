/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:47:03 by sandra            #+#    #+#             */
/*   Updated: 2024/06/10 16:36:09 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_cmd_table(t_token **cur, t_token *new, t_minishell *mini)
{
	int		i;
	t_token	*tmp;

	i = 0;
	printf("table -- type: %u \n", (*cur)->type);
	while (*cur && ((*cur)->type == COMMAND || (*cur)->type == BUILTIN \
		|| (*cur)->type == OPT || (*cur)->type == ARG || (*cur)->type == EMPTY))
	{
		if ((*cur)->type == EMPTY)
			new->tab[i] = ft_strdup("");
		else
			new->tab[i] = ft_strdup((*cur)->value);
		check_malloc_error(mini, new->tab,"Malloc in parser",  -1);
		printf("parse: %s\n", new->tab[i]);
		i++;
		tmp = (*cur)->next;
		free((*cur)->value);
		free(*cur);
		*cur = tmp;
	}
	new->tab[i] = NULL;
}

static int	count_token(t_token	*cur)
{
	int	i;

	i = 0;
	while (cur)
	{
		if (cur->type == OPT || cur->type == ARG || cur->type == EMPTY)
		i++;
		cur = cur->next;
	}
	return (i);
}

void	parse_commands(t_minishell *mini)
{
	t_token	*cur;
	t_token	*new;
	t_token	*prev;
	int		i;

	cur = mini->token;
	printf("----entered parse command ----\n");
	prev = NULL;
	while (cur)
	{
		if (cur && (cur->type == COMMAND || cur->type == BUILTIN \
			|| cur->type == OPT || cur->type == ARG || cur->type == EMPTY))
		{
			if (cur->type == BUILTIN)
			{
				if (prev == NULL)
					new = tok_new_node("builtin", BUILTIN, EMPTY);
				else
					new = tok_new_node("builtin", BUILTIN, prev->type);
			}
			else
			{
				if (prev == NULL)
					new = tok_new_node("command", COMMAND, EMPTY);
				else
					new = tok_new_node("command", COMMAND, prev->type);
			}
			check_malloc_error(mini, new, "Malloc in parse_command", -1);
			i = count_token(cur);
			new->tab = malloc((i + 2) * sizeof (char*));
			check_malloc_error(mini, new->tab, "Malloc in parse_command", -1);
			fill_cmd_table(&cur, new, mini);
			if (prev)
				prev->next = new;
			else
				mini->token = new;
			new->next = cur;
			prev = new;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}
