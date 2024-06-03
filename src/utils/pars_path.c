/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:31:52 by derjavec          #+#    #+#             */
/*   Updated: 2024/06/03 14:17:44 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pars_path(t_minishell *minishell)
{
	char	*path;
	char	**split_paths;

	path = get_env_value(minishell->env, "PATH");
	if (!path)
		ft_error("Malloc in ft_strdup", minishell);
	split_paths = ft_split(path, ':');
	if (!split_paths)
		return (NULL);
	free(path);
	return (split_paths);
}
