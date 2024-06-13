/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/13 19:58:00 by skanna           ###   ########.fr       */
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

// int	init_fds(t_mini *mini)
// {
// 	int	i;

// 	i = 0;
// 	mini->cmd_count = ft_cmd_count(mini);
// 	mini->fd_in = malloc(mini->cmd_count * sizeof(int));
// 	if (mini->fd_in == NULL)
// 		return (ft_error("Malloc in execution", mini), 1);
// 	while (i < mini->cmd_count)
// 		mini->fd_in[i++] = 0;
// 	mini->fd_out = malloc(mini->cmd_count * sizeof(int));
// 	if (mini->fd_out == NULL)
// 		return (ft_error("Malloc in execution", mini), 1);
// 	i = 0;
// 	while (i < mini->cmd_count)
// 		mini->fd_out[i++] = 1;
// 	mini->pid = malloc(mini->cmd_count * sizeof(pid_t));
// 	if (mini->pid == NULL)
// 		return (ft_error("Malloc in execution", mini), 1);
// 	mini->tube = malloc((mini->cmd_count - 1) * sizeof(*mini->tube));
// 	if (mini->tube == NULL)
// 		return (ft_error("Malloc in execution", mini), 1);
// 	i = 0;
// 	while (i < mini->cmd_count)
// 		mini->pid[i++] = 0;
// 	return (0);
// }


int	init_fds(t_mini *mini)
{
	int	i;

	mini->cmd_count = ft_cmd_count(mini);
	if (mini->cmd_count == 0)
		return (0);
	mini->fd_in = malloc(mini->cmd_count * sizeof(int));
	mini->fd_out = malloc(mini->cmd_count * sizeof(int));
	mini->pid = malloc(mini->cmd_count * sizeof(pid_t));
	if (!mini->fd_in || !mini->fd_out || !mini->pid)
		return (ft_error("Malloc in execution", mini), 1);
	if (mini->cmd_count > 1)
	{
		mini->tube = malloc((mini->cmd_count - 1) * sizeof(*mini->tube));
		if (!mini->tube)
			return (ft_error("Malloc in execution", mini), 1);
	}
	i = 0;
	while (i < mini->cmd_count)
	{
		mini->fd_in[i] = 0;
		mini->fd_out[i] = 1;
		mini->pid[i] = 0;
		i++;
	}
	return (0);
}
