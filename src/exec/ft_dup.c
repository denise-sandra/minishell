/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/24 13:55:58 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_dup_in_out(t_mini *mini, int i)
{
	if (mini->fd_in[i] != STDIN_FILENO)
	{
		printf("lala2\n");
		if (dup2(mini->fd_in[i], STDIN_FILENO) == -1)
		{
			close(mini->fd_in[i]);
			return (ft_error(mini, NULL, strerror(errno)), 1);
		}
		close(mini->fd_in[i]);
	}
	if (mini->fd_out[i] != STDOUT_FILENO)
	{
		printf("lala1\n");
		if (dup2(mini->fd_out[i], STDOUT_FILENO) == -1)
		{
			close(mini->fd_out[i]);
			return (ft_error(mini, NULL, strerror(errno)), 1);
		}
		close(mini->fd_out[i]);
	}
	return (0);
}

int	ft_dup(t_mini *mini, int i)
{
	if (ft_dup_in_out(mini, i) != 0)
		return (1);
	if (mini->cmd_count != 1 && ft_dup_tubes(mini, i) != 0)
		return (1);
	return (0);
}
