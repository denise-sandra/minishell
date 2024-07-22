/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/10 17:24:12 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_exec(t_mini *mini)
{
	if (mini->fd_in[0] > 0)
		close(mini->fd_in[0]);
	if (mini->fd_out[0] > 1)
		close(mini->fd_out[0]);
	if (mini->inv_fd[0] == 1)
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
	fill_fd(mini);
	if (mini->cmd_count <= 0)
		return (close_exec(mini));
	if (mini->cmd_count == 1 && tmp->type == COMMAND)
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

// grep <Makefile -v >outfile1 'A'
