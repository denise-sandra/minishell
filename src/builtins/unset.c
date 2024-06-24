/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/06/24 15:20:13 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_cmd_utils(t_mini *mini, t_token *cur, int i)
{
	t_lst_env	*prev;
	t_lst_env	*tmp;
	size_t		len;

	len = ft_strlen(cur->cmd_tab[i]);
	tmp = mini->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, cur->cmd_tab[i], len) == 0)
		{
			if (prev == NULL)
				mini->env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			tmp = NULL;
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void	unset_cmd(t_mini *mini, t_token *cur)
{
	int		i;
	int		changed;

	i = 1;
	changed = 0;
	while (cur->cmd_tab[i])
	{
		changed = unset_cmd_utils(mini, cur, i);
		i++;
	}
	if (changed == 1)
	{
		free(mini->env_char);
		mini->env_char = list_to_tab(mini);
	}
}
