/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/30 19:47:43 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_ret_message(t_token *cur)
{
	if (cur->cmd_tab[0][0] == '/')
		return (-3);
	return (-2);
}

int	is_accessible(t_mini *mini, t_token *cur)
{
	struct stat	statbuf;

	if (access(cur->cmd_tab[0], F_OK) == -1)
	{
		if (errno == ENOTDIR)
		{
			mini->exit_status = 126;
			ft_putstr_fd(cur->cmd_tab[0], 2);
			ft_putstr_fd(": Not a directory\n", 2);
			return (-4);
		}
		else
			return (manage_ret_message(cur));
	}
	if (stat(cur->cmd_tab[0], &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
			return (-1);
	}
	if (access(cur->cmd_tab[0], X_OK) == -1)
		return (-2);
	return (1);
}
