/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:31:52 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/17 15:20:38 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pars_path(t_minishell *minishell)
{
	char	*path;
	char	**split_paths;

	path = get_env_value(minishell->env, "PATH");
	if (!path)
	{
		printf("PATH environment variable not found\n");
		return (NULL);
	}
	split_paths = ft_split(path, ':');
	if (!split_paths)
		return (NULL);
	return (split_paths);
}
