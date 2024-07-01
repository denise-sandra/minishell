/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_script.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/01 21:28:06 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_shebang(t_mini *mini, int script)
{
	char    *line;
	char    *shebang;

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
				return (ft_error(mini, NULL, strerror(errno)), NULL);
			shebang[ft_strlen(shebang) - 1] = '\0';
			break ;
		}
		else if (strncmp(line, "#", 1) != 0)
		{
			shebang = ft_strdup("/bin/sh");
			if (!shebang)
				return (ft_error(mini, NULL, strerror(errno)), NULL);
		}
		free(line);
	}
	return (shebang);
}

static char	*get_script_name(t_token *tmp)
{
	char	*name;

	name = NULL;
	if (ft_strncmp(tmp->cmd_tab[0], "./", 2) == 0)
		name = tmp->cmd_tab[0] + 2;
	else if (ft_strncmp(tmp->cmd_tab[0], "sh", ft_strlen(tmp->cmd_tab[0])) == 0
		|| ft_strncmp(tmp->cmd_tab[0], "bash", ft_strlen(tmp->cmd_tab[0])) == 0)
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

static int	is_directory(const char *path)
{
	struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return (0);
    return S_ISDIR(statbuf.st_mode);
}

int	exec_script(t_mini *mini, t_token *tmp)
{
	int		script;
	char	*name;
	char	*args[3];

	name = get_script_name(tmp);
	init_args(args);
	if (name)
	{
		script = open(name, O_RDONLY);
		if (is_directory(name))
            return (ft_error(mini, " is a directory", NULL), 1);
		if (script == -1)
				return (ft_error(mini, NULL, strerror(errno)), 1);
		if (ft_strncmp(name + ft_strlen(name) - 3, ".sh", 3) == 0)
			args[0] = get_shebang(mini, script);
		close(script);
		if (!args[0])
			return (1);
		args[1] = name;
		args[2] = NULL;
		if (execve(args[0], args, mini->env_char) == -1)
		{
			ft_error(mini, NULL, strerror(errno));
			return (close(script), 1);
		}		
	}
	return (0);
}
