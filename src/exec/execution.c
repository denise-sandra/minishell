/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/31 11:32:15 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_and_wait_helper(int *status, int *exit, int *quit)
{
	if (WTERMSIG(*status) == SIGQUIT && !*quit)
	{
		*exit = 131;
		*quit = 1;
	}
	else if (WTERMSIG(*status) == SIGINT)
		*exit = 130;
}

static void	handle_signals_and_wait(t_mini *mini)
{
	int	i;
	int	status;
	int	last_exit_status;
	int	signal_received;
	int	quit_printed;

	i = 0;
	status = 0;
	last_exit_status = 0;
	signal_received = 0;
	quit_printed = 0;
	while (i < mini->pipe_count)
	{
		waitpid(mini->pid[i], &status, 0);
		if (WIFEXITED(status))
			last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			signal_received = 1;
			sig_and_wait_helper(&status, &last_exit_status, &quit_printed);
		}
		i++;
	}
	if (signal_received)
		mini->exit_status = last_exit_status;
}

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
	fill_fd(mini);
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
	handle_signals_and_wait(mini);
}
