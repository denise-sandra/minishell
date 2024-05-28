/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:53:57 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/28 13:56:28 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_builtin(t_minishell *minishell)
{
	minishell->builtin[0] = "echo";
	minishell->builtin[1] = "cd";
	minishell->builtin[2] = "pwd";
	minishell->builtin[3] = "export";
	minishell->builtin[4] = "unset";
	minishell->builtin[5] = "env";	
}

t_minishell	*init_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (minishell == NULL)
		ft_error("Malloc for minishell structure", minishell);
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->env = fill_env_struct(envp, minishell);
	init_builtin(minishell);
	return (minishell);
}
