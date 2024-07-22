/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_tubes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/10 17:26:22 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_inv_fd(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->pipe_count)
	{
		if (mini->inv_fd[i] == 1)
		{
			mini->error = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	first_command(t_mini *mini)
{
	close(mini->tube[0][0]);
	if (dup2(mini->tube[0][1], mini->fd_out[0]) == -1)
	{
		if (check_inv_fd(mini) == 0)
			ft_error(mini, NULL, strerror(errno));
		return (1);
	}
	close(mini->tube[0][1]);
	return (0);
}

static int	middle_command(t_mini *mini, int i)
{
	int	j;

	close(mini->tube[i][0]);
	if (dup2(mini->tube[i][1], mini->fd_out[i]) == -1)
	{
		if (check_inv_fd(mini) == 0)
			ft_error(mini, NULL, strerror(errno));
		return (1);
	}	
	j = 0;
	while (j < i + 1)
		close(mini->tube[j++][1]);
	if (dup2(mini->tube[i - 1][0], mini->fd_in[i]) == -1)
	{
		if (check_inv_fd(mini) == 0)
			ft_error(mini, NULL, strerror(errno));
		return (1);
	}	
	j = 0;
	while (j < i)
		close(mini->tube[j++][0]);
	return (0);
}

static int	last_command(t_mini *mini, int i)
{
	int	j;

	j = 0;
	while (j < i)
		close(mini->tube[j++][1]);
	if (dup2(mini->tube[i - 1][0], mini->fd_in[i]) == -1)
	{
		if (check_inv_fd(mini) == 0)
			ft_error(mini, NULL, strerror(errno));
		return (1);
	}	
	j = 0;
	while (j < i)
		close(mini->tube[j++][0]);
	return (0);
}

int	dup_tubes(t_mini *mini, int i)
{
	int	res;

	if (i == 0)
		res = first_command(mini);
	else if (i == mini->pipe_count - 1)
		res = last_command(mini, i);
	else
		res = middle_command(mini, i);
	if (res == 1)
		return (1);
	return (0);
}
