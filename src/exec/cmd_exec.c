/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/21 13:11:29 by deniseerjav      ###   ########.fr       */
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

static int	exec_script(t_mini *mini, t_token *tmp)
{
	int	script;
	char *name;
	char *line;
	char *args[3];
	
	name = NULL;
	if (ft_strncmp(tmp->cmd_tab[0], "./", 2) == 0)
		name = tmp->cmd_tab[0] + 2;
	else if (ft_strncmp(tmp->cmd_tab[0], "sh", ft_strlen(tmp->cmd_tab[0])) == 0 ||\
	ft_strncmp(tmp->cmd_tab[0], "bash", ft_strlen(tmp->cmd_tab[0])) == 0)
		name = tmp->cmd_tab[1];
	if (name)
	{
		script = open(name, O_RDONLY);
		if (script == -1)
		{
			close (script);
			return (ft_error(mini, NULL, strerror(errno)), 1);
		}
		args[0] = NULL;
		while (1)
		{
			line = get_next_line(script);
			if (!line)
				break;
			else if (strncmp(line, "#!", 2) == 0)
			{
				args[0] = ft_strdup(line + 2);
				free (line);
				if (!args[0])
					return (close(script), ft_error(mini, NULL, strerror(errno)), 1);
				args[0][ft_strlen(args[0]) - 1] = '\0';
				break ;
			}
			else if (strncmp(line, "#", 1) != 0)
			{
				args[0] = ft_strdup("/bin/sh");
				break ;
			}
			free(line);	
		}
		if (!args[0])
			return (close(script), 1);
		args[1] = name;
		args[2] = NULL;
		if (execve(args[0], args, mini->env_char) == -1) 
		{
            ft_error(mini, "", strerror(errno));
            return (free(args[0]), close(script), 1);
        }
		return (free(args[0]), close(script), ft_error(mini, "not found", NULL), 1);
	}
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
