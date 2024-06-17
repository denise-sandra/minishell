/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/17 12:58:52 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_mini *minishell, char *command)
{
	if (ft_strncmp(command, "export", 6) == 0)
		return (export_command(minishell), 0);
	else if (ft_strncmp(command, "env", 3) == 0)
		return (env_command(minishell), 0);
	else if (ft_strncmp(command, "echo", 4) == 0)
		return (echo_command(minishell), 0);
	else if (ft_strncmp(command, "pwd", 3) == 0)
		return (pwd_cmd(minishell), 0);
	else if (ft_strncmp(command, "cd", 2) == 0)
		return (cd_cmd(minishell), 0);
	else
		return (1);
}
