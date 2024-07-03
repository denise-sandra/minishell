/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/03 14:11:11 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_dup_in_out(t_mini *mini, int i)
{
	int	j;

	if (mini->fd_in[i] > 0 && mini->fd_in[i] != STDIN_FILENO)
	{
		if (dup2(mini->fd_in[i], STDIN_FILENO) == -1)
		{
			close(mini->fd_in[i]);
			close(mini->fd_out[i]);
			return (ft_error(mini, NULL, strerror(errno)), 1);
		}
	}
	else if (mini->fd_in[i] < 0)
	{
		if (i < mini->cmd_count - 1)
		{
			close(mini->tube[i][0]);
			close(mini->tube[i][1]);
		}
		return (ft_error(mini, NULL, strerror(errno)), 1);
	}
	j = 0;
	while (j <= i && mini->fd_in[j] != STDIN_FILENO)
	{
		if (mini->fd_in[j] > 0)
			close(mini->fd_in[j]);
		j++;
	}
	if (mini->fd_out[i] != STDOUT_FILENO)
	{
		if (dup2(mini->fd_out[i], STDOUT_FILENO) == -1)
		{
			close(mini->fd_out[i]);
			close(mini->fd_in[i]);
			return (ft_error(mini, NULL, strerror(errno)), 1);
		}
	}
	j = 0;
	while (j <= i && mini->fd_out[j] != STDOUT_FILENO)
	{
		if (mini->fd_out[j] > 0)
			close(mini->fd_out[j]);
		j++;
	}
	return (0);
}

int	ft_dup(t_mini *mini, int i)
{
	if (ft_dup_in_out(mini, i) != 0)
		return (1);
	if (mini->cmd_count != 1 && dup_tubes(mini, i) != 0)
		return (1);
	return (0);
}
