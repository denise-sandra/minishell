/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_subtoken.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:58:03 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/28 15:09:42 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst_token *ft_lstnew_st(void *content)
{
	t_lst_token	*new;

	new = malloc(sizeof(t_lst_token **));
	if (!new)
		return (NULL);
	new->value = ft_strdup((char *)content);
	if (new->value == NULL)
		return (NULL);
	new->subtype = OTHER;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_st(t_lst_token **lst, t_lst_token *new)
{
	t_lst_token *temp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_lstlast_t(*lst);
		temp->next = new;
	}
}

int		ft_lst_len_st(t_lst_token **lst)
{
	t_lst_token *tmp;
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

void	ft_lstdelone_st(t_lst_token *lst, void (*del)(void *))
{
	t_lst_token *temp;

	if (!lst)
		return ;
	temp = lst->next;
	if (!del)
		return ;
	del(lst->value);
	free(lst);
	lst = temp;
}

void	ft_lstclear_st(t_lst_token **lst, void (*del)(void *))
{
	t_lst_token *temp;

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

t_lst_token	*ft_lstlast_st(t_lst_token *lst)
{
	t_lst_token	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}