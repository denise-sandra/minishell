/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/10 11:25:19 by sandra           ###   ########.fr       */
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
	char	*p;
	int		command_found;

	i = 0;
	command_found = 0;
	if (tmp->cmd_tab[0][0] == '/')
		return (is_slash(mini, tmp));
	while (paths[i])
	{
		p = join_path(tmp->cmd_tab[0], paths[i]);
		if (!p)
			return (ft_error(mini, NULL, strerror(errno)), -1);
		if (access(p, X_OK) == 0)
		{
			command_found = 1;
			if (execve(p, tmp->cmd_tab, mini->env_char) == -1)
				return (free(p), ft_error(mini, NULL, strerror(errno)), -1);
		}
		free(p);
		i++;
	}
	if (!command_found)
		return (-2);
	return (0);
}

void	execve_failed(t_mini *mini, t_token *tmp, char **paths, int exec_ret)
{
	int		exit_tmp;

	if (exec_ret == -2)
	{
		mini->exit_status = 127;
		ft_putstr_fd(tmp->cmd_tab[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free(paths);
	}
	else
		free_tab(paths);
	exit_tmp = mini->exit_status;
	clean_minishell(mini);
	exit(exit_tmp);
}

void	cmd_exec(t_mini *mini, t_token *tmp)
{
	char	**paths;
	int		exec_ret;

	printf("entra a cmd_exe\n");
	if (exec_script(mini, tmp) == 1)
		return ;
	paths = pars_path(mini);
	if (paths == NULL)
		return (ft_error(mini, NULL, strerror(errno)));
	if (paths[0] == NULL)
	{
		free(paths);
		mini->exit_status = 127;
		ft_putstr_fd(tmp->cmd_tab[0], 2);
		return (ft_error(mini, " : No such file or directory\n", NULL));
	}
	exec_ret = cmd_exec_utils(mini, tmp, paths);
	if (exec_ret < 0)
		execve_failed(mini, tmp, paths, exec_ret);
}
