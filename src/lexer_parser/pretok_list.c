/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pretok_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:05:15 by skanna            #+#    #+#             */
/*   Updated: 2024/06/04 16:17:39 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pre_tag(char c)
{
	if (c == 32)
		return (WHITE);
	if (c == 34)
		return (D_Q);
	if (c == 36)
		return (EXP);
	if (c == 39)
		return (S_Q);
	if (c == 45)
		return (OPT);
	if (c == 60)
		return (IN);
	if (c == 62)
		return (OUT);
	if (c == 124)
		return (PIPE);
	return (CHAR);
}

t_pretok	*pretok_new_node(char c)
{
	t_pretok	*new;

	new = malloc(sizeof(t_pretok));
	if (!new)
		return (NULL);
	new->c = c;
	new->type = pre_tag(c);
	new->next = NULL;
	return (new);
}

void	pretok_addback(t_pretok **lst, t_pretok *new)
{
	t_pretok	*current;

	current = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}
