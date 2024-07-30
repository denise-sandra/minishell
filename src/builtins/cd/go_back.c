/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_back.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/07/29 17:10:20 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pwd_cmd_char(t_mini *mini)
{
	char	*cwd;
	int		size;

	size = 1024;
	cwd = malloc((size) * sizeof(char));
	if (cwd == NULL)
		return (ft_error(mini, NULL, strerror(errno)), NULL);
	if (getcwd(cwd, size) == NULL)
		return (free(cwd), ft_error(mini, NULL, strerror(errno)), NULL);
	return (cwd);
}

void	go_back(t_mini *mini)
{
	char	*path;
	char	*new_path;
	char	*root;
	int		c;

	path = pwd_cmd_char(mini);
	root = ft_strdup("/");
	if (!path || !root || \
		ft_strncmp(path, root, longer_len((char *)path, root)) == 0)
		return (free(path), free(root));
	free(root);
	c = ft_strrchr_int(path, '/');
	if (c == -1)
		return (free (path), ft_error(mini, "invalid path", NULL));
	new_path = malloc((c + 1) * sizeof(char));
	if (new_path == NULL)
		return (free(path), ft_error(mini, NULL, strerror(errno)));
	ft_strlcpy(new_path, path, c + 1);
	free(path);
	if (chdir(new_path) != 0)
	{
		free(new_path);
		return (ft_error(mini, NULL, strerror(errno)));
	}
	free(new_path);
}
