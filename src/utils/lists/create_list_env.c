/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:58:03 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/15 12:23:52 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst_env	*ft_lstnew_env(char *name, char *value)
{
	t_lst_env	*new;

	new = malloc(sizeof(t_lst_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (new->name == NULL)
		return (NULL);
	new->value = ft_strdup(value);
	if (new->value == NULL)
		return (NULL);
	new->next = NULL;
	return (new);
}

t_lst_env	*ft_lstlast_env(t_lst_env *lst)
{
	t_lst_env	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	ft_lstadd_back_env(t_lst_env **lst, t_lst_env *new)
{
	t_lst_env	*current;

	if (lst && new)
	{
		current = *lst;
		if (current == NULL)
		{
			*lst = new;
			return ;
		}
		while (current ->next != NULL)
		{
			current = current ->next;
		}
		current ->next = new;
	}
	return ;
}
