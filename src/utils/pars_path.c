/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:31:52 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/14 20:24:40 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pars_path(t_minishell *minishell)
{
	char	*path;
	char	**split_paths;
	char	special_c[2];

	special_c[0] = '\'';
	special_c[1] = '\0';
	path = get_env_value(minishell->env, "PATH");
	printf("path: %s\n", path);
	if (!path)
	{
		printf("PATH environment variable not found\n");
		return (NULL);
	}
	split_paths = ft_split(path, ':', special_c);
	if (!split_paths)
		return (NULL);
	return (split_paths);
}
