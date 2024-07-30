/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/30 19:03:30 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(t_mini *mini, t_token *cur)
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
			return (-2);
	}
	if (stat(cur->cmd_tab[0], &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
			return (-3);
	}
	if (access(cur->cmd_tab[0], X_OK) == -1)
		return (-2);
	return (1);
}
