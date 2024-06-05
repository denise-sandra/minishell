/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/05 03:27:35 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_minishell *minishell, char *command)
{
	if (ft_strncmp(command, "export", 6) == 0)
		export_command(minishell);
	else if (ft_strncmp(command, "env", 3) == 0)
		env_command(minishell);
	else if (ft_strncmp(command, "echo", 4) == 0)
		echo_command(minishell);
	else
		printf("special command not yet coded\n");
}
