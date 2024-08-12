/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/08/12 09:18:00 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tmp(t_lst_env	*tmp)
{
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	tmp = NULL;
}

static int	update_export(t_mini *mini, t_token *cur, int i, int len)
{
	t_lst_env	*prev;
	t_lst_env	*tmp;

	tmp = mini->export;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, cur->cmd_tab[i], len) == 0)
		{
			if (prev == NULL)
				mini->export = tmp->next;
			else
				prev->next = tmp->next;
			free_tmp(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

static int	update_env(t_mini *mini, t_token *cur, int i, int len)
{
	t_lst_env	*prev;
	t_lst_env	*tmp;

	tmp = mini->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, cur->cmd_tab[i], len) == 0)
		{
			if (prev == NULL)
				mini->env = tmp->next;
			else
				prev->next = tmp->next;
			free_tmp(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

static int	unset_cmd_utils(t_mini *mini, t_token *cur, int i)
{
	size_t		len;

	len = ft_strlen(cur->cmd_tab[i]);
	if (len == 0)
		return (0);
	if (cur->cmd_tab[i][0] == '-')
	{
		mini->exit_status = 2;
		return (ft_error(mini, " invalid option", NULL), -1);
	}
	if (update_env(mini, cur, i, len) != 0)
		return (1);
	if (update_export(mini, cur, i, len) != 0)
		return (1);
	return (0);
}

void	unset_cmd(t_mini *mini, t_token *cur)
{
	int		i;
	int		changed;

	i = 1;
	changed = 0;
	mini->exit_status = 0;
	while (cur->cmd_tab[i])
	{
		changed = unset_cmd_utils(mini, cur, i);
		if (changed == -1)
			break ;
		i++;
	}
	if (changed == 1)
	{
		free_tab(mini->env_char);
		mini->env_char = list_to_tab(mini);
	}
}
