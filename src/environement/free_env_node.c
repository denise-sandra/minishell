/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/08/08 12:19:32 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_utils(t_mini *mini, t_lst_env **temp, \
	t_lst_env **prev, t_lst_env **next)
{
	free((*temp)->name);
	free((*temp)->value);
	if ((*temp)->next)
		*next = (*temp)->next;
	free(*temp);
	if (*prev)
		(*prev)->next = *next;
	else
		mini->env = *next;
}

void	free_env_node(t_mini *mini, t_lst_env *env, char *name)
{
	t_lst_env	*temp;
	t_lst_env	*prev;
	t_lst_env	*next;
	size_t		len;

	temp = env;
	prev = NULL;
	next = NULL;
	len = ft_strchr_int(name, '=');
	if ((int)len == -1)
		len = ft_strlen(name);
	while (temp)
	{
		if (ft_strlen(temp->name) == len && \
			ft_strncmp(temp->name, name, len) == 0)
		{
			free_env_utils(mini, &temp, &prev, &next);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}
