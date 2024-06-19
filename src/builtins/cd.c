/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/06/19 17:06:56 by skanna           ###   ########.fr       */
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
		return (ft_error("Malloc error", mini), NULL);
	if (getcwd(cwd, size) == NULL)
		return (ft_error("pwd error", mini), NULL);
	return (cwd);
}

int	ft_strrchr_int(char *str, int c)
{
	int	size;

	size = ft_strlen(str);
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

static void	go_home(t_mini *mini)
{
	char	*path;

	path = get_env_value(mini->env, "HOME");
	if (path == NULL)
		return (ft_error("Malloc error", mini));
	if (chdir(path) != 0)
		return (free(path), ft_error("cd: No such file or directory", mini));
	else
		free (path);
}

static void	go_back(t_mini *mini)
{
	char	*path;
	char	*new_path;
	int		c;

	path = pwd_cmd_char(mini);
	c = ft_strrchr_int(path, '/');
	printf("%d\n", c);
	new_path = malloc((c + 1) * sizeof(char));
	if (new_path == NULL)
		return (ft_error("Malloc error", mini));
	ft_strlcpy(new_path, path, c);
	printf("%s\n", new_path);
	free(path);
	if (chdir(new_path) != 0)
	{
		free(new_path);
		return (ft_error("cd: No such file or directory", mini));
	}
	free(new_path);
}

void	cd_cmd(t_mini *mini)
{
	const char	*path;

	if (mini->token->cmd_tab[2])
		return (ft_error("cd: too many arguments", mini));
	path = mini->token->cmd_tab[1];
	if (!path || ft_strncmp(path, "~", ft_strlen(path)) == 0)
		go_home(mini);
	else if (ft_strncmp(path, "..", ft_strlen(path)) == 0)
		go_back(mini);
	else if (chdir(path) != 0)
		return (ft_error("cd: No such file or directory", mini));
}
