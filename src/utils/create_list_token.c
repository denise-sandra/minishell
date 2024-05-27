/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:58:03 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/27 14:35:20 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst_token *ft_lstnew_t(void *content)
{
	t_lst_token	*new;

	new = malloc(sizeof(t_lst_token **));
	if (!new)
		return (NULL);
	new->value = content;
	new->type = OTHER;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_t(t_lst_token **lst, t_lst_token *new)
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

int		ft_lst_len(t_lst_token **lst)
{
	t_lst_token *tmp;
    int len;
    
    tmp = *lst;
    len = 0;
    while (tmp)
    {
        len =+ ft_strlen(tmp->value);
        tmp = tmp->next;
    }
    return (len);
}

void	ft_lstdelone_t(t_lst_token *lst, void (*del)(void *))
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

void	ft_lstclear_t(t_lst_token **lst, void (*del)(void *))
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