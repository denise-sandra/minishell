/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/08/09 16:29:49 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*init_minishell(char **envp)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (mini == NULL)
	{
		ft_putstr_fd("Failed to malloc minishell structure\n", 2);
		exit(1);
	}
	ft_bzero(mini, sizeof(t_mini));
	if (envp[0] == NULL)
		envp = no_env(mini);
	mini->env = fill_env_struct(envp, mini);
	if (!mini->env)
		return (clean_minishell(mini), NULL);
	mini->export = copy_list(mini->env);
	if (!mini->export)
	{
		ft_error(mini, "Failed to copy envp", NULL);
		return (clean_minishell(mini), NULL);
	}
	if (handle_shlvl(mini) == 1)
		return (clean_minishell(mini), NULL);
	return (mini);
}
