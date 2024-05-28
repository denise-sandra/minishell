/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:58:03 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/28 15:10:32 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_lstnew_t(void *content)
{
	t_token	*new;

	new = malloc(sizeof(t_lst_token **));
	if (!new)
		return (NULL);
	new->value = ft_strdup((char *)content);
	if (!new->value)
		return (NULL);
	new->type = -1;
	new->subtoken = NULL;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_t(t_token **lst, t_token *new)
{
	t_token *temp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_lstlast_t(*lst);
		temp->next = new;
	}
}

int		ft_lst_len_t(t_token **lst)
{
	t_token *tmp;
	int len;

    tmp = *lst;
    len = 0;
    while (tmp)
    {
        len += ft_strlen(tmp->value);
        tmp = tmp->next;
    }
    return (len);
}

void	ft_lstdelone_t(t_token *lst, void (*del)(void *))
{
	t_token *temp;

	if (!lst)
		return ;
	temp = lst->next;
	if (!del)
		return ;
	del(lst->value);
	free(lst);
	lst = temp;
}

void	ft_lstclear_t(t_token **lst, void (*del)(void *))
{
	t_token *temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if (del)
			del((*lst)->value);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

t_token	*ft_lstlast_t(t_token *lst)
{
	t_token	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}