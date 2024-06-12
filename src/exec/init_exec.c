/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/12 15:18:05 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cmd_count(t_mini *mini)
{
	 t_token *tmp;
	 int  count;

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


void	init_fds(t_mini *mini)
{
	int i;
	
	i = 0;
	mini->cmd_count = ft_cmd_count(mini);
	mini->fd_in = malloc(mini->cmd_count * sizeof(int));
    if (mini->fd_in == NULL)
		return (ft_error("Malloc in execution", mini));
	while(i < mini->cmd_count)
          mini->fd_in[i++] = 0;
	mini->fd_out = malloc(mini->cmd_count * sizeof(int));
     if (mini->fd_out == NULL)
		return (ft_error("Malloc in execution", mini));
     i = 0;
	while(i < mini->cmd_count)
          mini->fd_out[i++] = 1;
	mini->pid = malloc(mini->cmd_count * sizeof(pid_t));
	if (mini->pid == NULL)
		return (ft_error("Malloc in execution", mini));
     i = 0;
	while(i < mini->cmd_count)
          mini->pid[i++] = 0;
}
