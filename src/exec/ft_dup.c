/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/14 15:56:32 by deniseerjav      ###   ########.fr       */
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

int	first_command(t_mini *mini)
{
	close(mini->tube[0][0]);
	if (dup2(mini->tube[0][1], mini->fd_out[0]) == -1)
		return (ft_error("fdup Error", mini), 1);
	close(mini->tube[0][1]);
	return (0);
}

int	middle_command(t_mini *mini, int i)
{
	int	j;

	close(mini->tube[i][0]);
	if (dup2(mini->tube[i][1], mini->fd_out[i]) == -1)
		return (ft_error("m2dup Error", mini), 1);
	j = 0;
	while (j <= i)
		close(mini->tube[j++][1]);
	j = 0;
	while (j < i - 1)
		close(mini->tube[j++][0]);
	if (dup2(mini->tube[i - 1][0], mini->fd_in[i]) == -1)
		return (ft_error("m1dup Error", mini), 1);
	close(mini->tube[i - 1][0]);
	return (0);
}

int	last_command(t_mini *mini, int i)
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

static int	ft_dup_tubes(t_mini *mini, int i)
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
	/*int	j;

	j = 0;
	printf("comandos totales: %i    cur cmd: %i\n", mini->cmd_count, i);//test
	while (j <= i)
	{
		printf("cerrado extremo 1 del tubo %d en el cmd %d\n", j, i);
		close(mini->tube[j++][1]);
	}
	while (j < i - 1)
		close(mini->tube[j++][0]);
	if ((i + 1) != mini->cmd_count)
		close(mini->tube[i][0]);
	if ((i + 1) != mini->cmd_count && dup2(mini->tube[i][1], mini->fd_out[i]) == -1)
	{
		printf("intento de dup2 i: %d \n", i);
		perror("dup :");
		return (ft_error("1dup Error", mini), 1);
	}	
	if ((i + 1) != mini->cmd_count)
		close(mini->tube[i][1]);
	j = 0;
	if (i < mini->cmd_count - 1)//test
   		printf("intento de dup2 fd %d a %d\n", mini->tube[i][1], mini->fd_out[i]);
	if (i > 0 && dup2(mini->tube[i - 1][0], mini->fd_in[i]) == -1)
	{
		printf("intento de dup2 i: %d \n", i);
		perror("dup :");
		return (ft_error("2dup Error", mini), 1);
	}	
	if (i > 0)
		 close(mini->tube[i - 1][0]);*/
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
