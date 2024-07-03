/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/07/03 19:40:17 by skanna           ###   ########.fr       */
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

int	ft_strrchr_int(char *str, int c)
{
	int	size;

	if (!str)
		return (-1);
	size = ft_strlen(str) - 1;
	if (str[size] == (char)c)
		size--;
	while (size >= 0)
	{
		if (str[size] == (char)c)
			return (size + 1);
		size--;
	}
	return (-1);
}

void	go_home(t_mini *mini)
{
	char	*path;

	path = get_env_value(mini->env, "HOME");
	if (path == NULL)
		return (ft_error(mini, NULL, strerror(errno)));
	if (chdir(path) != 0)
		return (free(path), ft_error(mini, NULL, strerror(errno)));
	else
		free (path);
}

static void	go_back(t_mini *mini)
{
	char	*path;
	char	*new_path;
	int		c;

	path = pwd_cmd_char(mini);
	if (!path)
		return ;
	c = ft_strrchr_int(path, '/');
	if (c == -1)
	{
		free (path);
		return (ft_error(mini, "Can't go back or invalid path", NULL));
	}
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

void	cd_cmd(t_mini *mini, t_token *cur)
{
	const char	*path;
	int			count;

	if (!cur->cmd_tab)
		return ;
	count = 0;
	while (cur->cmd_tab[count])
		count++;
	if (count == 3)
		return (ft_error(mini, " too many arguments", NULL));
	path = cur->cmd_tab[1];
	if (count == 1 || !path || ft_strncmp(path, "~", ft_strlen(path)) == 0)
		go_home(mini);
	else if (ft_strncmp(path, "..", ft_strlen(path)) == 0)
		go_back(mini);
	else if (chdir(path) != 0)
		return (ft_error(mini, NULL, strerror(errno)));
}
