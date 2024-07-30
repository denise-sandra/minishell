/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:16:30 by skanna            #+#    #+#             */
/*   Updated: 2024/07/30 19:07:04 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	execute_command(t_mini *mini, char **cmd, char **sh_argv)
// {
// 	int		ret;

// 	ret = execve(cmd[0], cmd, mini->env_char);
// 	if (ret == -1)
// 	{
// 		if (errno == ENOEXEC)
// 		{
// 			ret = execve("/bin/sh", sh_argv, mini->env_char);
// 			if (ret == -1)
// 				return (ft_error(mini, NULL, strerror(errno)), -1);
// 		}
// 		else
// 			return (ft_error(mini, NULL, strerror(errno)), -1);
// 	}
// 	return (0);
// }

static void	free_content(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
}

int	is_abs_or_relative(t_mini *mini, t_token *tmp, char **paths)
{
	char	*sh_argv[3];
	int		ret;

	ret = 0;
	sh_argv[0] = "/bin/sh";
	sh_argv[1] = tmp->cmd_tab[0];
	sh_argv[2] = NULL;
	if (ft_strchr(tmp->cmd_tab[0], '/') || tmp->cmd_tab[0][0] == '.')
	{
		ret = is_directory(mini, tmp);
		if (ret == -4)
			return (-4);
		if (ret == -3)
			return (-3);
		if (ret == -2)
			return (free_content(paths), -2);
		if (ret == -1)
		{
			mini->exit_status = 126;
			ft_putstr_fd(tmp->cmd_tab[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			return (-1);
		}
	}
	return (1);
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
	if (joint_b == NULL)
		return (NULL);
	return (joint_b);
}

int	cmd_exec_utils(t_mini *mini, t_token *tmp, char **paths)
{
	int		i;
	char	*p;
	int		ret;

	i = 0;
	ret = is_abs_or_relative(mini, tmp, paths);
	if (ret != 1)
		return (ret);
	while (paths[i])
	{
		p = join_path(tmp->cmd_tab[0], paths[i]);
		if (!p)
			return (ft_error(mini, NULL, strerror(errno)), -1);
		if (access(p, X_OK) == 0)
		{
			if (execve(p, tmp->cmd_tab, mini->env_char) == -1)
				return (ft_error(mini, NULL, strerror(errno)), -1);
			return (free(p), 0);
		}
		free(p);
		i++;
	}
	return (-2);
}
