/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/06/19 12:06:45 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst_env	*copy_list(t_lst_env *lst)
{
	t_lst_env *new;
	t_lst_env *new_lst;

	new_lst = NULL;
	while (lst)
	{
		new = ft_lstnew_env(lst->name, lst->value);
		if (!new)
			return (NULL);
		ft_lstadd_back_env(&new_lst, new);
		lst = lst->next;
	}
	return (new_lst);
}