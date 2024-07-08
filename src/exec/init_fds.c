/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/03 13:33:14 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cmd_count(t_mini *mini)
{
	t_token	*tmp;
	int		count;

	tmp = mini->token;
	count = 0;
	while (tmp)
	{
		if (tmp->type == COMMAND)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static void	init_fds(t_mini *mini, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		if (i < j - 1)
		{
			mini->tube[i][0] = 0;
			mini->tube[i][1] = 0;
		}
		mini->fd_in[i] = 0;
		mini->fd_out[i] = 1;
		mini->inv_fd[i] = 0;
		mini->pid[i] = 0;
		i++;
	}
}

int	malloc_fds(t_mini *mini)
{
	int	j;

	mini->cmd_count = ft_cmd_count(mini);
	j = mini->cmd_count;
	if (mini->cmd_count == 0)
		j = 1;
	mini->fd_in = malloc(j * sizeof(int));
	mini->fd_out = malloc(j * sizeof(int));
	mini->inv_fd = malloc(j * sizeof(int));
	mini->pid = malloc(j * sizeof(pid_t));
	if (!mini->fd_in || !mini->fd_out || !mini->pid || !mini->inv_fd)
		return (ft_error(mini, NULL, strerror(errno)), 1);
	if (mini->cmd_count > 1)
	{
		mini->tube = malloc((mini->cmd_count - 1) * sizeof(*mini->tube));
		if (!mini->tube)
			return (ft_error(mini, NULL, strerror(errno)), 1);
	}
	init_fds(mini, j);
	return (0);
}
