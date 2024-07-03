/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/03 14:53:50 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_mini *mini)
{
	t_token	*tmp;
	int		builtin;

	tmp = mini->token;
	builtin = -1;
	if (malloc_fds(mini) != 0)
		return ;
	if (fill_fd(mini) != 0)
		return ;
	if (mini->cmd_count <= 0)
	{
		if (mini->fd_in[0] > 0)
			close(mini->fd_in[0]);
		if (mini->fd_out[0] > 1)
			close(mini->fd_out[0]);
		return ;
	}
	if (tmp->type == COMMAND)
		builtin = is_builtin(tmp->cmd_tab[0]);
	if (mini->cmd_count == 1 && builtin > 0)
	{
		builtin_in_parent(mini, builtin);
		return ;
	}
	exec_in_child(mini, tmp);
	if (mini->error)
		return ;
	close_fd_and_wait(mini);
}


// grep <Makefile -v >outfile1 'A'
