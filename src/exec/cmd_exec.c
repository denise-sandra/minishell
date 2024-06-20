/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/20 11:52:33 by deniseerjav      ###   ########.fr       */
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

static void cmd_exec_utils(t_mini *mini, t_token *tmp, char	**paths)
{
    int		i;
    char	*path_with_token;
    
    i = 0;
    while (paths[i])
	{
		path_with_token = join_path(tmp->cmd_tab[0], paths[i]);
		if (!path_with_token)
			return (ft_error("Malloc error", mini));
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
}

void	cmd_exec(t_mini *mini, t_token *tmp)
{
	char	**paths;

	paths = pars_path(mini);
	if (paths == NULL)
		return (ft_error("Memory allocation error in execution", mini));
	cmd_exec_utils(mini, tmp, paths);
    if (mini->error)
        return (free(paths));
	printf("%s :command not found\n", tmp->cmd_tab[0]);
	free(paths);
	exit(127);
}