/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/08/05 16:47:14 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_exec(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->pipe_count)
	{
		if (mini->fd_in[i] > 0)
			close(mini->fd_in[i]);
		if (mini->fd_out[i] > 1)
			close(mini->fd_out[i]);
		i++;
	}
	if (mini->inv_fd[0] != 0)
		mini->exit_status = 1;
}

void	execution(t_mini *mini)
{
	t_token	*tmp;
	int		builtin;

	tmp = mini->token;
	builtin = -1;
	if (malloc_fds(mini) != 0)
		return ;
	fill_fd(mini, tmp);
	if (mini->error != 0)
		return ;
	if (mini->cmd_count <= 0)
		return (close_exec(mini));
	if (mini->pipe_count == 1 && tmp->type == COMMAND)
		builtin = is_builtin(tmp->cmd_tab[0]);
	if (mini->cmd_count == 1 && builtin > 0)
	{
		builtin_in_parent(mini, builtin);
		return ;
	}
	exec_in_child(mini, tmp);
	if (mini->error)
		return ;
	close_fd_and_wait(mini);
}
