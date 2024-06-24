/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/06/24 13:39:03 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void unset_cmd(t_mini *mini, t_token *cur)
{
	t_lst_env *tmp;
	t_lst_env *prev;
	size_t      len;
	int       i;
	int       changed;

	i = 1;
	changed = 0;
	while (cur->cmd_tab[i])
	{
		len = ft_strlen(cur->cmd_tab[i]);
		tmp = mini->env;
		while (tmp)
		{
			if (ft_strncmp(tmp->name, cur->cmd_tab[i], len) == 0)
			{
				changed = 1;
				if (prev == NULL)
					mini->env = tmp->next;
				else
					prev->next = tmp->next;
				free(tmp->name);
				free(tmp->value);
				free(tmp);
				tmp = NULL;
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	if (changed == 1)
	{
		free(mini->env_char);
		mini->env_char = list_to_tab(mini);
	}
}