/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:53:57 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/22 12:31:53 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_special_commands(t_minishell *minishell)
{
	minishell->special_commands[0] = "echo";
	minishell->special_commands[1] = "cd";
	minishell->special_commands[2] = "pwd";
	minishell->special_commands[3] = "export";
	minishell->special_commands[4] = "unset";
	minishell->special_commands[5] = "env";	
}

t_minishell	*init_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (minishell == NULL)
		ft_error("Malloc for minishell structure", minishell);
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->env = fill_env_struct(envp, minishell);
	init_special_commands(minishell);
	return (minishell);
}
