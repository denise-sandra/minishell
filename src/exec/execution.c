/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/13 14:00:49 by deniseerjav      ###   ########.fr       */
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

static void	cmd_exec(t_mini *mini, t_token *tmp)
{
	int	i;
	char	**paths;
	char	*path_with_token;

	i = 0;
	paths = pars_path(mini);
	if (paths == NULL)
		return (ft_error("Memory allocation error in execution", mini));
	while (paths[i])
	{
		path_with_token = join_path(tmp->cmd_tab[0], paths[i]);
		if (!path_with_token)
			return (free(paths));
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

void	execution(t_mini *mini)
{
	t_token	*tmp;
	int		i;
	
	if (init_fds(mini) != 0)
		return ;
	if (fill_fd(mini) != 0)
		return ;
	i = 0;
	tmp = mini->token;
	while (tmp)
	{
		if (tmp->type == COMMAND)
		{
			if ((i + 1) != mini->cmd_count && pipe(mini->tube[i]) == -1)
				return (ft_error("Error while piping", mini));
			mini->pid[i] = fork();
			if (mini->pid[i] < 0)
				return (ft_error("Fork error", mini));
			if (mini->pid[i] == 0)
			{
				if (ft_dup(mini, i) != 0)
					return ;
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
