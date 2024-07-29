/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/29 08:54:02 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execve_failed(t_mini *mini, t_token *tmp, \
char **paths, int exec_ret)
{
	int		exit_tmp;

	if (exec_ret == -2)
	{
		mini->exit_status = 127;
		ft_putstr_fd(tmp->cmd_tab[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free(paths);
		close_all_fd(mini);
	}
	else
		free_tab(paths);
	exit_tmp = mini->exit_status;
	clean_minishell(mini);
	exit(exit_tmp);
}

static char	**pars_path(t_mini *mini)
{
	char	*path;
	char	**split_paths;
	char	cwd[1024];

	path = get_env_value(mini->env, "PATH");
	if (!path)
		return (NULL);
	if (path[0] == '\0')
	{
		if (getcwd(cwd, 1024) == NULL)
			return (ft_error(mini, NULL, strerror(errno)), NULL);
		path = ft_strdup(cwd);
		if (path == NULL)
			return (NULL);
	}
	split_paths = ft_split(path, ':');
	free(path);
	return (split_paths);
}

static int	check_path_null(t_mini *mini, char **paths, t_token *tmp)
{
	if (!paths[0])
	{
		free(paths);
		mini->exit_status = 127;
		ft_putstr_fd(tmp->cmd_tab[0], 2);
		return (1);
	}
	return (0);
}

static int	check_if_empty(t_mini *mini, t_token *tmp)
{
	if (!tmp->cmd_tab[0] || tmp->cmd_tab[0][0] == '\0')
	{
		mini->exit_status = 127;
		ft_putstr_fd(tmp->cmd_tab[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (1);
	}
	return (0);
}

void	cmd_exec(t_mini *mini, t_token *tmp)
{
	char	**paths;
	int		exec_ret;

	if (check_if_empty(mini, tmp) != 0)
		return ;
	paths = pars_path(mini);
	if (!paths)
		return (ft_error(mini, NULL, strerror(errno)));
	if (check_path_null(mini, paths, tmp) != 0)
		return (ft_error(mini, " : No such file or directory\n", NULL));
	if (ft_strncmp(tmp->cmd_tab[0], "./minishell", \
	longer_len(tmp->cmd_tab[0], "./minishell")) == 0)
	{
		if (handle_shlvl(mini) != 0)
			return (free(paths), ft_error(mini, "Can't update SHLVL\n", NULL));
	}
	exec_ret = cmd_exec_utils(mini, tmp, paths);
	if (exec_ret < 0)
		execve_failed(mini, tmp, paths, exec_ret);
	else
		free_tab(paths);
}
