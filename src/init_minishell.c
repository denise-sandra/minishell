/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:53:57 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/14 19:52:09 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*init_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (minishell == NULL)
		ft_error("Malloc for minishell structure", minishell);
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->env = malloc(sizeof(t_environement));
	if (!minishell->env)
		ft_error("Malloc for minishell->env", minishell);
	*(minishell->env) = env_fill_structure(envp, minishell);
	return (minishell);
}
