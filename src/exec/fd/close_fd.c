/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/08/09 16:43:21 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd_and_wait(t_mini *mini)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < mini->pipe_count)
	{
		if (mini->fd_in && mini->fd_in[i] > 0 && mini->fd_in[i] != STDIN_FILENO)
			close(mini->fd_in[i]);
		if (mini->fd_out && mini->fd_out[i] > 0 \
			&& mini->fd_out[i] != STDOUT_FILENO)
			close(mini->fd_out[i]);
		i++;
	}
	i = 0;
	while (i < mini->pipe_count)
	{
		waitpid(mini->pid[i], &status, 0);
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
		check_sigs(mini);
		i++;
	}
}

void	close_all_fd(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->pipe_count)
	{
		if (mini->fd_in[i] > 2)
			close(mini->fd_in[i]);
		if (mini->fd_out[i] > 2)
			close(mini->fd_out[i]);
		i++;
	}
}

void	close_all_tubes(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->pipe_count)
	{
		if (i < mini->pipe_count - 1)
		{
			if (mini->tube[i][1])
				close(mini->tube[i][1]);
			if (mini->tube[i][0])
				close(mini->tube[i][0]);
		}
		i++;
	}
}

void	close_if_inv_fd(t_mini *mini, int j)
{
	int	i;

	i = j;
	if (mini->inv_fd[j] == 1)
	{
		close_all_tubes(mini);
		close_all_fd(mini);
		clean_minishell(mini);
		exit (1);
	}
}
