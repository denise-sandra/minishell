/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/13 14:04:32 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_dup_in_out(t_mini *mini, int i)
{
	if (mini->fd_in[i] != STDIN_FILENO)
	{
		if (dup2(mini->fd_in[i], STDIN_FILENO) == -1)
		{
			close(mini->fd_in[i]);
			return (ft_error("dup Error", mini), 1);
		}
		close(mini->fd_in[i]);
	}
	if (mini->fd_out[i] != STDOUT_FILENO)
	{
		if (dup2(mini->fd_out[i], STDOUT_FILENO) == -1)
		{
			close(mini->fd_out[i]);
			return (ft_error("dup Error", mini), 1);
		}
		close(mini->fd_out[i]);
	}
	return (0);
}

static int	ft_dup_tubes(t_mini *mini, int i)
{
	int	j;

	if ((i + 1) != mini->cmd_count)
	{
		j = 0;
		while (j < i)
			close(mini->tube[j++][1]);
		close(mini->tube[i][0]);
		if (dup2(mini->tube[i][1], mini->fd_out[i]) == -1)
			return (ft_error("dup Error", mini), 1);
        close(mini->tube[i][1]);
		j = 0;
		while (j < i)
			close(mini->tube[j++][0]);
		if (i > 0 && dup2(mini->tube[i - 1][0], mini->fd_in[i]) == -1)
			return (ft_error("dup Error", mini), 1);	
	}
	return (0);
}

int	ft_dup(t_mini *mini, int i)
{
	if (ft_dup_in_out(mini, i) != 0)
		return (1);
	if (ft_dup_tubes(mini, i) != 0)
		return (1);
	return (0);
}
