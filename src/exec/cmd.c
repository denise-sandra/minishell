/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/20 11:26:34 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	first_command(t_mini *mini)
{
	close(mini->tube[0][0]);
	if (dup2(mini->tube[0][1], mini->fd_out[0]) == -1)
		return (ft_error("fdup Error", mini), 1);
	close(mini->tube[0][1]);
	return (0);
}

static int	middle_command(t_mini *mini, int i)
{
	int	j;

	close(mini->tube[i][0]);
	if (dup2(mini->tube[i][1], mini->fd_out[i]) == -1)
		return (ft_error("m2dup Error", mini), 1);
	j = 0;
	while (j < i + 1)
		close(mini->tube[j++][1]);
	if (dup2(mini->tube[i - 1][0], mini->fd_in[i]) == -1)
		return (ft_error("m1dup Error", mini), 1);
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
		return (ft_error("ldup Error", mini), 1);
	j = 0;
	while (j < i)
		close(mini->tube[j++][0]);
	return (0);
}

int	ft_dup_tubes(t_mini *mini, int i)
{
	int	res;

	if (i == 0)
		res = first_command(mini);
	else if (i == mini->cmd_count - 1)
		res = last_command(mini, i);
	else
		res = middle_command(mini, i);
	if (res == 1)
		return (1);
	return (0);
}