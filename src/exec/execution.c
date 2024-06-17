/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/17 12:46:46 by derjavec         ###   ########.fr       */
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
			{
				ft_error("execve Error", mini);
				exit(1);
			}
		}
		free(path_with_token);
		i++;
	}
	printf("%s :command not found\n", tmp->cmd_tab[0]);
	free(paths);
	//clean_minishell(mini);
	//exit(1);
}

static void	close_fd_and_wait(t_mini *mini)
{
	int	i;
	int	status;
	// pid_t pid;

	i = 0;
	while (i < mini->cmd_count)
	{
		if (mini->fd_in && mini->fd_in[i] != STDIN_FILENO)
			close(mini->fd_in[i]);
		if (mini->fd_out && mini->fd_out[i] != STDOUT_FILENO)
			close(mini->fd_out[i]);
		waitpid(mini->pid[i++], &status, 0);
	}
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
				{
					cmd_exec(mini, tmp);
					if (mini->error)
						return ;
				}
			}
			if (i > 0)
            {
				//waitpid(mini->pid[i - 1], NULL, 0);
				printf("%d cerrado en parent\n", i - 1);
                close(mini->tube[i - 1][0]);
                close(mini->tube[i - 1][1]);
            }
			i++;
		}
		tmp = tmp->next;
	}
	close_fd_and_wait(mini);
	//test
	// int status;
	// pid_t pid;

	// while ((pid = wait(&status)) != -1)
	// {
	// 	if (WIFEXITED(status))
	// 		printf("Child %d exited with status %d\n", pid, WEXITSTATUS(status));
	// 	else if (WIFSIGNALED(status))
	// 		printf("Child %d killed by signal %d\n", pid, WTERMSIG(status));
	// }
}
