/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_back.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/07/22 11:41:10 by derjavec         ###   ########.fr       */
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
	char	*home;
	int		c;

	path = pwd_cmd_char(mini);
	home = get_env_value(mini->env, "HOME");
	if (!path || !home || \
		ft_strncmp(path, home, longer_len((char *)path, home)) == 0)
		return (free(path), free(home));
	free(home);
	c = ft_strrchr_int(path, '/');
	if (c == -1)
		return (free (path), ft_error(mini, "invalid path", NULL));
	new_path = malloc((c + 1) * sizeof(char));
	if (new_path == NULL)
		return (free(path), ft_error(mini, NULL, strerror(errno)));
	ft_strlcpy(new_path, path, c);
	free(path);
	if (chdir(new_path) != 0)
	{
		free(new_path);
		return (ft_error(mini, NULL, strerror(errno)));
	}
	free(new_path);
}
