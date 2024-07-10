/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_script.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/10 10:00:17 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_shebang(t_mini *ms, int script, char *shebang)
{
	char	*line;

	shebang = NULL;
	while (1)
	{
		line = get_next_line(script);
		if (!line)
			break ;
		else if (ft_strncmp(line, "#!", 2) == 0)
		{
			shebang = ft_strdup(line + 2);
			if (!shebang)
				return (free(line), ft_error(ms, NULL, strerror(errno)), NULL);
			shebang[ft_strlen(shebang) - 1] = '\0';
			break ;
		}
		else if (strncmp(line, "#", 1) != 0)
		{
			shebang = ft_strdup("/bin/sh");
			if (!*shebang)
				return (free(line), ft_error(ms, NULL, strerror(errno)), NULL);
		}
		free(line);
	}
	return (shebang);
}

static char	*get_script_name(t_token *tmp)
{
	char	*name;

	name = NULL;
	if (ft_strncmp(tmp->cmd_tab[0], ".", longer_len(tmp->cmd_tab[0], ".")) == 0)
		return (NULL);
	if (ft_strncmp(tmp->cmd_tab[0], "./", longer_len(tmp->cmd_tab[0], "./")) == 0)
		name = tmp->cmd_tab[0] + 2;
	else if (ft_strncmp(tmp->cmd_tab[0], "sh", longer_len(tmp->cmd_tab[0], "sh")) == 0
		|| ft_strncmp(tmp->cmd_tab[0], "bash", longer_len(tmp->cmd_tab[0], "bash")) == 0)
		name = tmp->cmd_tab[1];
	return (name);
}

static void	init_args(char **args)
{
	static char	empty[] = "";

	args[0] = empty;
	args[1] = empty;
	args[2] = empty;
}

static int	process_script(t_mini *mini, const char *name, int *script_fd)
{
	struct stat	statbuf;
	int			script;

	script = open(name, O_RDONLY);
	if (script == -1)
	{
		if (errno == EACCES)
			mini->exit_status = 126;
		else
			mini->exit_status = 127;
		return (ft_error(mini, NULL, strerror(errno)), 1);
	}
	if (stat(name, &statbuf) != 0)
		return (close(script), ft_error(mini, "Failed to stat file", NULL), 1);
	if (S_ISDIR(statbuf.st_mode))
	{
		close(script);
		mini->exit_status = 126;
		return (ft_error(mini, "Is a directory", NULL), 1);
	}
	*script_fd = script;
	return (0);
}

int	exec_script(t_mini *mini, t_token *tmp)
{
	char	*name;
	int		script;
	char	*args[3];

	name = get_script_name(tmp);
	if (!name)
		return (ft_error(mini, " filename argument required", NULL), 1);
	init_args(args);
	if (name)
	{
		if (process_script(mini, name, &script) != 0)
			return (1);
		if (ft_strncmp(name + ft_strlen(name) - 3, ".sh", 3) == 0)
			args[0] = get_shebang(mini, script, args[0]);
		if (!args[0])
			return (close(script), 1);
		args[1] = name;
		args[2] = NULL;
		if (execve(args[0], args, mini->env_char) == -1)
		{
			mini->exit_status = 127;
			return (close(script), ft_error(mini, NULL, strerror(errno)), 1);
		}
		close(script);
	}
	return (0);
}
