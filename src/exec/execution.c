/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/25 14:18:59 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd_and_wait(t_mini *mini)
{
	int	i;
	int	status;
	int	last_exit_status;

	i = 0;
	last_exit_status = 0;
	while (i < mini->cmd_count)
	{
		if (mini->fd_in &&  mini->fd_in[i] > 0 && mini->fd_in[i] != STDIN_FILENO)
			close(mini->fd_in[i]);
		if (mini->fd_out && mini->fd_out[i] > 0 && mini->fd_out[i] != STDOUT_FILENO)
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

static void	child_pid(t_mini *mini, t_token *tmp, int i)
{
	int		builtin;

	if (ft_dup(mini, i) != 0)
	{
		clean_minishell(mini);
		exit (1);
	}
	builtin = is_builtin(tmp->cmd_tab[0]);
	if (builtin > 0)
		execute_builtin(mini, builtin, tmp);
	else
		cmd_exec(mini, tmp);
	if (mini->error)
	{
		clean_minishell(mini);
		exit (1);
	}
	clean_minishell(mini);
	exit (0);
}

static void	exec_in_child(t_mini *mini, t_token *tmp)
{
	int		i;

	i = 0;
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

static int	builtin_in_parent(t_mini *mini)
{
	t_token	*tmp;
	int		builtin;

	tmp = mini->token;
	while (tmp->type != COMMAND)
		tmp = tmp->next;
	builtin = is_builtin(tmp->cmd_tab[0]);
	if (mini->cmd_count == 1 && builtin > 0)
		return (execute_builtin(mini, builtin, mini->token), 1);
	return (0);
}

void	execution(t_mini *mini)
{
	t_token	*tmp;

	if (init_fds(mini) != 0)
		return ;
	if (fill_fd(mini) != 0)
		return ;
	if (mini->cmd_count <= 0)
		return ;
	if (builtin_in_parent(mini) != 0)
		return ;
	tmp = mini->token;
	exec_in_child(mini, tmp);
	if (mini->error)
		return ;
	close_fd_and_wait(mini);
}
