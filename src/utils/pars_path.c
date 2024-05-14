/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:31:52 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/13 11:31:53 by derjavec         ###   ########.fr       */
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
	split_paths = ft_split(path, ':', special_c);
	if (path == NULL || split_paths == NULL)
		ft_error("path spliting error", minishell);
	return (split_paths);
}