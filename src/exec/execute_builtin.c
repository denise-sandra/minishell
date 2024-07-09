/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/09 16:21:10 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{

	if (ft_strncmp(command, "export", longer_len(command, "export")) == 0)
		return (1);
	else if (ft_strncmp(command, "env", longer_len(command, "env")) == 0 \
		|| ft_strncmp(command, "env", longer_len(command, "ENV")) == 0)
		return (2);
	else if (ft_strncmp(command, "echo", longer_len(command, "echo")) == 0)
		return (3);
	else if (ft_strncmp(command, "pwd", longer_len(command, "pwd")) == 0)
		return (4);
	else if (ft_strncmp(command, "cd", longer_len(command, "cd")) == 0)
		return (5);
	else if (ft_strncmp(command, "unset", longer_len(command, "unset")) == 0)
		return (6);
	else if (ft_strncmp(command, "exit", longer_len(command, "exit")) == 0)
		return (7);
	else
		return (0);
}

void	execute_builtin(t_mini *mini, int builtin, t_token *cur)
{
	if (builtin == 1)
		export_command(mini, cur);
	else if (builtin == 2)
		env_command(mini);
	else if (builtin == 3)
		echo_command(cur);
	else if (builtin == 4)
		pwd_cmd(mini);
	else if (builtin == 5)
		cd_cmd(mini, cur);
	else if (builtin == 6)
		unset_cmd(mini, cur);
	else if (builtin == 7)
		exit_cmd(mini, cur->cmd_tab);
}
