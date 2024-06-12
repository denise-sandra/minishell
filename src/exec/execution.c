/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/12 16:09:24 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**pars_path(t_mini *mini)
{
	char	*path;
	char	**split_paths;

	path = get_env_value(mini->env, "PATH");
	check_malloc_error(mini, path, "Malloc in exectution", -1);
	split_paths = ft_split(path, ':');
	if (!split_paths)
		return (NULL);
	free(path);
	return (split_paths);
}

static char	*join_path(t_mini *mini, char *cmd, char *path)
{
	char	*joint_a;
	char	*joint_b;

	joint_a = ft_strjoin_char(path, '/');
	check_malloc_error(mini, joint_a, "Malloc in exectution", -1);
	joint_b = ft_strjoin(joint_a, cmd);
	check_malloc_error(mini, joint_b, "Malloc in exectution", -1);
	free(joint_a);
	return (joint_b);
}

static void	cmd_exec(t_mini *mini, t_token *tmp)
{
	int		i;
	char	**paths;
	char	*path_with_token;

	i = 0;
	paths = pars_path(mini);
	if (paths == NULL)
		return (ft_error("Memory allocation error in execution", mini));
	while (paths[i])
	{
		path_with_token = join_path(mini, tmp->cmd_tab[0], paths[i]);
		if (access(path_with_token, X_OK) == 0)
		{
			if (execve(path_with_token, tmp->cmd_tab, mini->env_char) == -1)
				return (ft_error("execve Error", mini));
		}
		free(path_with_token);
		i++;
	}
	free(paths);
}

static void	ft_dup(t_mini *mini, int i)
{
	//printf("mini in: %i    mini out: %i\n", mini->fd_in[i], mini->fd_out[i]);
	if (mini->fd_in[i] != STDIN_FILENO)
	{
		if (dup2(mini->fd_in[i], STDIN_FILENO) == -1)
		{
			close(mini->fd_in[i]);
			ft_error("dup Error", mini);
		}
		close(mini->fd_in[i]);
	}
	if (mini->fd_out[i] != STDOUT_FILENO)
	{
		if (dup2(mini->fd_out[i], STDOUT_FILENO) == -1)
		{
			close(mini->fd_out[i]);
			ft_error("dup Error", mini);
		}
		close(mini->fd_out[i]);
	}
}

void	execution(t_mini *mini)
{
	t_token	*tmp;
	int		i;

	init_fds(mini);
	fill_fd(mini);
	i = 0;
	tmp = mini->token;
	while (tmp)
	{
		if (tmp->type == COMMAND)
		{
			mini->pid[i] = fork();
			if (mini->pid[i] < 0)
				return (ft_error("Fork error", mini));
			if (mini->pid[i] == 0)
			{
				ft_dup(mini, i);
				if (execute_builtin(mini, tmp->cmd_tab[0]) == 0)
					return ;
				else
					return (cmd_exec(mini, tmp));
			}
			i++;
		}
		tmp = tmp->next;
	}
	i = 0;
	while (i < mini->cmd_count)
	{
		if (mini->fd_in && mini->fd_in[i] != STDIN_FILENO)
			close(mini->fd_in[i]);
		if (mini->fd_out && mini->fd_out[i] != STDOUT_FILENO)
			close(mini->fd_out[i]);
		waitpid(mini->pid[i++], NULL, 0);
	}
}
