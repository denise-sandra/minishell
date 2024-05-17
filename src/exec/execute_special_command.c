/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/17 09:16:20 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_special_command(t_minishell *minishell, char *command)
{
	if (ft_strncmp(command, "export", 6) == 0)
		export_command(minishell);
	else if (ft_strncmp(command, "env", 3) == 0)
		env_command(minishell);
	else
		printf("special command not yet coded\n");
}