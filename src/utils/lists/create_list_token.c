/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:58:03 by derjavec          #+#    #+#             */
/*   Updated: 2024/06/03 14:42:38 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_lstnew_t(void *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup((char *)content);
	if (!new->value)
		return (NULL);
	new->type = OTHER;
	new->sub_token = NULL;
	new->next = NULL;
	return (new);
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
	t_token	*tmp;
	int		len;

	tmp = *lst;
	len = 0;
	while (tmp)
	{
		len += ft_strlen(tmp->value);
		tmp = tmp->next;
	}
	return (len);
}

// void	ft_lstdelone_t(t_token *lst, void (*del)(void *))
// {
// 	t_token *temp;

// 	if (!lst)
// 		return ;
// 	temp = lst->next;
// 	if (!del)
// 		return ;
// 	del(lst->value);
// 	if (lst->sub_token)
// 	{
// 		clean_token_list(&lst->sub_token);
// 		lst->sub_token = NULL;
// 	}
// 	free(lst);
// 	lst = temp;
// }

// void	ft_lstclear_t(t_token **lst)
// {
// 	t_token	*temp;

// 	if (!lst)
// 		return ;
// 	while (*lst)
// 	{
// 		temp = (*lst)->next;
// 		if ((*lst)->value)
// 			free((*lst)->value);
// 		if ((*lst)->sub_token)
// 			clean_subtokens((*lst)->sub_token);
// 		free(*lst);
// 		*lst = temp;
// 	}
// 	*lst = NULL;
// }

