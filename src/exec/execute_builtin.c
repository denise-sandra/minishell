/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/19 17:00:05 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	size_t	len;

	len = ft_strlen(command);
	if (ft_strncmp(command, "export", len) == 0)
		return (1);
	else if (ft_strncmp(command, "env", len) == 0)
		return (2);
	else if (ft_strncmp(command, "echo", len) == 0)
		return (3);
	else if (ft_strncmp(command, "pwd", len) == 0)
		return (4);
	else if (ft_strncmp(command, "cd", len) == 0)
		return (5);
	else if (ft_strncmp(command, "unset", len) == 0)
		return (6);
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
		cd_cmd(mini);
}


// void	execute_commands(t_mini *mini, char *command, t_token *cur)
// {
// 	int	builtin;

// 	builtin = is_builtin(command);
// 	if (builtin > 0)
// 		execute_builtin(mini, builtin, cur);
// 	else
// 		cmd_exec(mini, cur);
// }