/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_slash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/05 09:36:27 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_directory_from_home(t_mini *mini)
{
	struct stat	statbuf;
	char			cwd[1024];

	if (getcwd(cwd, 1024) == NULL)
		return (ft_error(mini, NULL, strerror(errno)), -1);
	if (stat(mini->token->cmd_tab[0], &statbuf) != 0)
	{
		if (chdir(cwd) != 0)
			return (ft_error(mini, NULL, strerror(errno)), -1);
		return (0);
	}
	if (chdir(cwd) != 0)
		return (ft_error(mini, NULL, strerror(errno)), -1);
	return (S_ISDIR(statbuf.st_mode));
}

int	is_slash(t_mini *mini, t_token *tmp)
{
	int		res;

	res = is_directory_from_home(mini);
	if (res == 1)
	{
		mini->exit_status = 126;
		return (ft_error(mini, " Is a directory", NULL), -3);
	}
	if (access(tmp->cmd_tab[0], F_OK) == 0)
	{
		if (execve(tmp->cmd_tab[0], tmp->cmd_tab, mini->env_char) == -1)
		{
			mini->exit_status = 1;
			return (ft_error(mini, NULL, strerror(errno)), -1);
		}
	}
	mini->exit_status = 127;
	return (ft_error(mini, NULL, strerror(errno)), -1);
}
