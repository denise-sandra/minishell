/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_in_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/03 15:48:54 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_pid(t_mini *mini, t_token *tmp, int i)
{
	int	exit_code;

	close_if_inv_fd(mini, i);
	exit_code = 0;
	if (ft_dup(mini, i) != 0)
	{
		exit_code = mini->exit_status;
		clean_minishell(mini);
		exit (exit_code);
	}
	if (is_builtin(tmp->cmd_tab[0]) > 0)
		execute_builtin(mini, is_builtin(tmp->cmd_tab[0]), tmp);
	else
		cmd_exec(mini, tmp);
	if (mini->error)
	{
		exit_code = mini->exit_status;
		clean_minishell(mini);
		exit (exit_code);
	}
	close_all_fd(mini);
	exit_code = mini->exit_status;
	clean_minishell(mini);
	exit (exit_code);
}

void	exec_in_child(t_mini *mini, t_token *cur)
{
	int  i;
	t_token	*tmp;

	i = 0;
	tmp = cur;
	while (tmp)
	{
		if (tmp->type == COMMAND)
		{
			if ((i + 1) != mini->cmd_count && pipe(mini->tube[i]) == -1)
				return (ft_error(mini, NULL, strerror(errno)));
			mini->pid[i] = fork();
			if (mini->pid[i] < 0)
				return (ft_error(mini, NULL, strerror(errno)));
			if (mini->pid[i] == 0)
				child_pid(mini, tmp, i);
			if (i > 0)
			{
				close(mini->tube[i - 1][0]);
				close(mini->tube[i - 1][1]);
			}
			i++;
		}
		tmp = tmp->next;
	}
}