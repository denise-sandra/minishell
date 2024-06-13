/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/13 15:09:15 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	first_command(t_mini *mini)
{
	close(mini->tube[0][0]);
	if (dup2(mini->tube[0][1], mini->fd_out[0]) == -1)
		return(ft_error("dup error", mini), 1);
	close(mini->tube[0][1]);
	return (0);
}

int	middle_command(t_mini *mini, int i)
{
	int	j;

	j = 0;
	while (j < i)
		close(mini->tube[j++][1]);
	close(mini->tube[i][0]);
	if (dup2(mini->tube[i - 1][0], mini->fd_in[i]) == -1)
		return(ft_error("dup error", mini), 1);
	j = 0;
	while (j < i)
		close(mini->tube[j++][0]);
	if (dup2(mini->tube[i][1], mini->fd_out[i]) == -1)
		return(ft_error("dup error", mini), 1);
	close(mini->tube[i][1]);
	return (0);
}

int	last_command(t_mini *mini, int i)
{
	int	j;

	j = 0;
	while (j < i)
		close(mini->tube[j++][1]);
	if (dup2(mini->tube[i - 1][0], mini->fd_in[i]) == -1)
		return(ft_error("dup error", mini), 1);
	j = 0;
	while (j < i)
		close(mini->tube[j++][0]);
	if (dup2(mini->fd_out[i], STDOUT_FILENO) == -1)
		return(ft_error("dup error", mini), 1);
	return (0);
}