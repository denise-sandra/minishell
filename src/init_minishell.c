/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:53:57 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/15 12:34:22 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_special_commands(t_minishell *minishell)
{
	minishell->special_commands[0] = "export";
	minishell->special_commands[1] = "env";
}

t_minishell	*init_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (minishell == NULL)
		ft_error("Malloc for minishell structure", minishell);
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->env = env_fill_structure(envp, minishell);
	init_special_commands(minishell);
	return (minishell);
}
