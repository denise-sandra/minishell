/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:58:03 by derjavec          #+#    #+#             */
/*   Updated: 2024/07/23 11:14:32 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	tok_delone(t_token **lst, t_token **prev)
{
	t_token	*temp;

	if (!lst)
		return ;
	temp = (*lst)->next;
	free((*lst)->value);
	free(*lst);
	*lst = temp;
	(*prev)->next = *lst;
}

t_token	*tok_new_node(char *content, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(content);
	if (!new->value)
		return (NULL);
	new->type = type;
	new->cmd_tab = NULL;
	new->next = NULL;
	return (new);
}

void	tok_addback(t_token **lst, t_token *new)
{
	t_token	*current;

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

int	tok_list(char *s, int type, t_token **lst)
{
	t_token	*new;

	new = tok_new_node(s, type);
	if (!new)
		return (1);
	tok_addback(lst, new);
	return (0);
}
