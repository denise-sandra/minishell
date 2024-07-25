/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_in_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/25 17:26:59 by skanna           ###   ########.fr       */
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

static void	pipe_if_no_cmd(t_mini *mini, int i)
{
	if ((i + 1) != mini->pipe_count && pipe(mini->tube[i]) == -1)
		return (ft_error(mini, NULL, strerror(errno)));
	if (i > 0)
	{
		close(mini->tube[i - 1][0]);
		close(mini->tube[i - 1][1]);
	}
}

static void	pipe_if_cmd(t_mini *mini, t_token *tmp, int i)
{
	if ((i + 1) != mini->pipe_count && pipe(mini->tube[i]) == -1)
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
}

// static void	handle_pipes(t_mini *mini, t_token *tmp, int *i, int *j)
// {
// 	if (tmp->type == PIPE)
// 		(*j)++;
// 	if (tmp->type == COMMAND)
// 	{
// 		pipe_if_cmd(mini, tmp, *i);
// 		(*i)++;
// 	}
// 	else if (*i < *j)
// 	{
// 		pipe_if_no_cmd(mini, *i);
// 		(*i)++;
// 	}
// }

void	exec_in_child(t_mini *mini, t_token *cur)
{
	t_token	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	tmp = cur;
	while (tmp)
	{
		// handle_pipes(mini, tmp, &i, &j);
		// printf("i: %i   j: %i\n", i, j);
		if (tmp->type == PIPE)
			j++;
		if (tmp->type == COMMAND)
		{
			pipe_if_cmd(mini, tmp, i);
			i++;
		}
		else if (i < j)
		{
			pipe_if_no_cmd(mini, i);
			i++;
		}
		tmp = tmp->next;
	}
	while (k < mini->pipe_count - 1)
	{
		close(mini->tube[k][0]);
		close(mini->tube[k][1]);
		k++;
	}
}
