/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_in_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/25 15:18:56 by derjavec         ###   ########.fr       */
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
	printf("sin cmd: %d\n", i);
	if (i > 0)
	{
		printf("cierra sin cmd\n");
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
	printf("con cmd: %d\n", i);
	if (i > 0)
	{
		printf("cierra con cmd\n");
		close(mini->tube[i - 1][0]);
		close(mini->tube[i - 1][1]);
	}
}

void	exec_in_child(t_mini *mini, t_token *cur)
{
	t_token	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = cur;
	while (tmp)
	{
		if (tmp->type == PIPE)
			j++;
		if (tmp->type == COMMAND)
		{
			pipe_if_cmd(mini, tmp, i);
			i++;
		}
		//printf("i: %d cur_pipes: %d\n", i, cur_pipes);
		else if (i < j)
		{
			pipe_if_no_cmd(mini, i);
			i++;
		}
		tmp = tmp->next;
	}
}
