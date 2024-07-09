/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/09 15:32:39 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd_and_wait(t_mini *mini)
{
	int	i;
	int	status;
	int	last_exit_status;

	i = 0;
	last_exit_status = 0;
	status = 0;
	while (i < mini->cmd_count)
	{
		if (mini->fd_in && mini->fd_in[i] > 0 && mini->fd_in[i] != STDIN_FILENO)
			close(mini->fd_in[i]);
		if (mini->fd_out && mini->fd_out[i] > 0 \
			&& mini->fd_out[i] != STDOUT_FILENO)
			close(mini->fd_out[i]);
		i++;
	}
	i = 0;
	while (i < mini->cmd_count)
	{
		waitpid(mini->pid[i], &status, 0);
		if (WIFEXITED(status))
			last_exit_status = WEXITSTATUS(status);
		i++;
	}
	mini->exit_status = last_exit_status;
}

void	close_all_fd(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->cmd_count)
	{
		if (i < mini->cmd_count - 1)
		{
			if (mini->tube[i][1])
				close(mini->tube[i][1]);
			if (mini->tube[i][0])
				close(mini->tube[i][0]);
		}
		if (mini->fd_in[i] > 0)
			close(mini->fd_in[i]);
		if (mini->fd_out[i] > 1)
			close(mini->fd_out[i]);
		i++;
	}
}

void	close_if_inv_fd(t_mini *mini, int j)
{
	int	i;

	i = j;
	while (i < mini->cmd_count)
	{
		if (mini->inv_fd[i] == 1)
			close_all_fd(mini);
		i++;
	}
	if (mini->inv_fd[j] == 1)
	{
		clean_minishell(mini);
		exit (1);
	}
}
