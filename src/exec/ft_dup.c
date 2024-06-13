/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/13 18:14:21 by skanna           ###   ########.fr       */
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

/*static int	last_command(t_mini *mini, int i)
{
	int	j;

	j = 0;
	while (j < i)
		close(mini->tube[j++][1]);
	if (dup2(mini->tube[i - 1][0], mini->fd_in[i]) == -1)
		return(ft_error("l1dup error", mini), 1);
	j = 0;
	while (j < i)
		close(mini->tube[j++][0]);
	if (dup2(mini->fd_out[i], STDOUT_FILENO) == -1)
		return(ft_error("l2dup error", mini), 1);
	return (0);
}

static int	middle_command(t_mini *mini, int i)
{
	int	j;

	j = 0;
	while (j < i)
		close(mini->tube[j++][1]);
	close(mini->tube[i][0]);
	if (dup2(mini->tube[i - 1][0], mini->fd_in[i]) == -1)
		return(ft_error("m1dup error", mini), 1);
	j = 0;
	while (j < i)
		close(mini->tube[j++][0]);
	if (dup2(mini->tube[i][1], mini->fd_out[i]) == -1)
		return(ft_error("m2dup error", mini), 1);
	close(mini->tube[i][1]);
	return (0);
}

static int	first_command(t_mini *mini)
{
	close(mini->tube[0][0]);
	if (dup2(mini->tube[0][1], mini->fd_out[0]) == -1)
		return(ft_error("fdup error", mini), 1);
	close(mini->tube[0][1]);
	return (0);
}*/

static int	ft_dup_tubes(t_mini *mini, int i)
{
    // if (i == 0 && first_command(mini) != 0)
    //     return (1);
    // else if (i + 1 != mini->cmd_count && middle_command(mini, i) != 0)
    //     return (1);
    // else if (i + 1 == mini->cmd_count && last_command(mini, i) != 0)
    //     return (1);
	int	j;

    j = 0;
    while (j < i)
        close(mini->tube[j++][1]);
    if ((i + 1) != mini->cmd_count)
        close(mini->tube[i][0]);
    if ((i + 1) != mini->cmd_count && dup2(mini->tube[i][1], mini->fd_out[i]) == -1)
        return (ft_error("1dup Error", mini), 1);
    if ((i + 1) != mini->cmd_count)
        close(mini->tube[i][1]);
    j = 0;
    while (j < i - 1)
        close(mini->tube[j++][0]);
    if (i > 0 && dup2(mini->tube[i - 1][0], mini->fd_in[i]) == -1)
        return (ft_error("2dup Error", mini), 1);
    if (i > 0)
         close(mini->tube[i - 1][0]);
	return (0);
}

int	ft_dup(t_mini *mini, int i)
{
	if (ft_dup_in_out(mini, i) != 0)
		return (1);
	if (mini->cmd_count < 1 && ft_dup_tubes(mini, i) != 0)
		return (1);
	return (0);
}
