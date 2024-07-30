/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_in_parent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/09 13:06:10 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	b_i_p_utils(t_mini *mini, int builtin, int stdin, int stdout)
{
	execute_builtin(mini, builtin, mini->token);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
	if (mini->error)
		return ;
	if (mini->fd_in[0] > 0)
		close(mini->fd_in[0]);
	if (mini->fd_out[0] > 1)
		close(mini->fd_out[0]);
}

void	builtin_in_parent(t_mini *mini, int builtin)
{
	t_token	*tmp;
	int		stdin;
	int		stdout;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (mini->inv_fd[0] == 1)
		return ;
	tmp = mini->token;
	while (tmp->type != COMMAND)
		tmp = tmp->next;
	if (mini->fd_in[0] > 0)
	{
		if (dup2(mini->fd_in[0], STDIN_FILENO) == -1)
			return (ft_error(mini, "dup2 stdin error", NULL));
	}
	if (mini->fd_out[0] > 1)
	{
		if (dup2(mini->fd_out[0], STDOUT_FILENO) == -1)
			return (ft_error(mini, "dup2 stdout error", NULL));
	}
	b_i_p_utils(mini, builtin, stdin, stdout);
	return ;
}
