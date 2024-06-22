/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/21 23:53:52 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**pars_path(t_mini *mini)
{
	char	*path;
	char	**split_paths;

	path = get_env_value(mini->env, "PATH");
	if (path == NULL)
		return (NULL);
	split_paths = ft_split(path, ':');
	free(path);
	return (split_paths);
}

static char	*join_path(char *cmd, char *path)
{
	char	*joint_a;
	char	*joint_b;

	joint_a = ft_strjoin_char(path, '/');
	if (joint_a == NULL)
		return (NULL);
	joint_b = ft_strjoin(joint_a, cmd);
	free(joint_a);
	return (joint_b);
}

static int	cmd_exec_utils(t_mini *mini, t_token *tmp, char **paths)
{
	int		i;
	char	*path_with_token;
	int		command_found;

	i = 0;
	command_found = 0;
	while (paths[i])
	{
		path_with_token = join_path(tmp->cmd_tab[0], paths[i]);
		if (!path_with_token)
			return (ft_error(mini, NULL, strerror(errno)), -1);
		if (access(path_with_token, X_OK) == 0)
		{
			command_found = 1;
			if (execve(path_with_token, tmp->cmd_tab, mini->env_char) == -1)
				return (free(path_with_token), \
				ft_error(mini, NULL, strerror(errno)), -1);
		}
		free(path_with_token);
		i++;
	}
	if (!command_found)
		return (-2);
	return (0);
}

void	cmd_exec(t_mini *mini, t_token *tmp)
{
	char	**paths;
	int		exec_ret;

	if (exec_script(mini, tmp) == 1)
		return ;
	paths = pars_path(mini);
	if (paths == NULL)
		return (ft_error(mini, "Failed to parse path", NULL));
	exec_ret = cmd_exec_utils(mini, tmp, paths);
	free(paths);
	if (exec_ret == -2)
	{
		ft_putstr_fd(tmp->cmd_tab[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		error_cleanup(mini);
		exit(127);
	}
	else if (exec_ret == -1)
	{
		ft_error(mini, NULL, strerror(errno));
		exit(127);
	}
}
