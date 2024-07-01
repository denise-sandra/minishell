/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/01 12:53:31 by derjavec         ###   ########.fr       */
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

static void	close_all_fd(t_mini *mini)
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
		if (mini->fd_in[i] > 0 && mini->fd_in[i] != STDIN_FILENO)
			close(mini->fd_in[i]);
		if (mini->fd_out[i] != STDOUT_FILENO)
			close(mini->fd_out[i]);
		i++;
	}
}

static void	close_if_inv_fd(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->cmd_count)
	{
		if (mini->inv_fd[i] == 1)
		{
			close_all_fd(mini);
			ft_putstr_fd(" No such file or directory\n", 2);
			clean_minishell(mini);
			exit (1);
		}
		i++;
	}
}

static void	child_pid(t_mini *mini, t_token *tmp, int i)
{
	int		builtin;

	close_if_inv_fd(mini);
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
	close_all_fd(mini);
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

static int	builtin_in_parent(t_mini *mini, int builtin)
{
	t_token	*tmp;
	int		original_stdin;
	int		original_stdout;

	// printf("inv %d\n", mini->inv_fd[0]);
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (mini->inv_fd[0] == 1)
		return (ft_error(mini, " No such file or directory", NULL), -1);
	tmp = mini->token;
	while (tmp->type != COMMAND)
		tmp = tmp->next;
	if (mini->fd_in[0] > 0)
	{
		if (dup2(mini->fd_in[0], STDIN_FILENO) == -1)
			return (ft_error(mini, "dup2 stdin error", NULL), -1);
	}
	if (mini->fd_out[0] > 1)
	{
		if (dup2(mini->fd_out[0], STDOUT_FILENO) == -1)
			return (ft_error(mini, "dup2 stdin error", NULL), -1);

	}
	if (mini->cmd_count == 1)
	{
		execute_builtin(mini, builtin, mini->token);
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdin);
		close(original_stdout);
		if (mini->fd_in[0] > 0)
			close(mini->fd_in[0]);
		if (mini->fd_out[0] > 1)
			close(mini->fd_out[0]);
		return (1);
	}
	return (0);
}

void	execution(t_mini *mini)
{
	t_token	*tmp;
	int		builtin;

	tmp = mini->token;
	builtin = -1;
	if (init_fds(mini) != 0)
		return ;
	if (fill_fd(mini) != 0)
		return ;
	if (mini->cmd_count <= 0)
	{
		if (mini->fd_in[0] > 0)
			close(mini->fd_in[0]);
		if (mini->fd_out[0] > 1)
			close(mini->fd_out[0]);
		if (mini->fd_in[0] < 0 || mini->fd_out[0] < 0)
			return (ft_error(mini, " No such file or directory", NULL));
		return ;
	}
	if (tmp->type == COMMAND)
		builtin = is_builtin(tmp->cmd_tab[0]);
	if (mini->cmd_count == 1 && builtin > 0 && builtin_in_parent(mini, builtin) != 0)
		return ;
	exec_in_child(mini, tmp);
	if (mini->error)
		return ;
	close_fd_and_wait(mini);
}


// grep <Makefile -v >outfile1 'A'
