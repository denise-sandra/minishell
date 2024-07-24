/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_script_bin_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/24 15:16:53 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_shebang(t_mini *ms, int script)
// {
// 	char	*line;
// 	char	*shebang;

// 	while (1)
// 	{
// 		line = get_next_line(script);
// 		if (!line)
// 			break ;
// 		else if (ft_strncmp(line, "!", 1) == 0)
// 		{
// 			shebang = ft_strdup(line + 1);
// 			if (!shebang)
// 				return (free(line), ft_error(ms, NULL, strerror(errno)), NULL);
// 			shebang[ft_strlen(shebang) - 1] = '\0';
// 			break ;
// 		}
// 		else if (strncmp(line, "#", 1) != 0)
// 		{
// 			shebang = ft_strdup("/bin/sh");
// 			if (!*shebang)
// 				return (free(line), ft_error(ms, NULL, strerror(errno)), NULL);
// 		}
// 		free(line);
// 	}
// 	return (shebang);
// }

// char	*get_name(t_token *tmp)
// {
// 	char	*name;

// 	name = NULL;
// 	if (ft_strncmp(tmp->cmd_tab[0], "./", 2) == 0)
// 		name = tmp->cmd_tab[0] + 2;
// 	else if (ft_strncmp(tmp->cmd_tab[0], "sh", \
// 		longer_len(tmp->cmd_tab[0], "sh")) == 0
// 		|| ft_strncmp(tmp->cmd_tab[0], "bash", \
// 				longer_len(tmp->cmd_tab[0], "bash")) == 0)
// 		name = tmp->cmd_tab[1];
// 	return (name);
// }

// int	process_file(t_mini *mini, const char *name, int *script_fd)
// {
// 	struct stat	statbuf;
// 	int			script;

// 	script = open(name, O_RDONLY);
// 	if (script == -1)
// 	{
// 		if (errno == EACCES)
// 			mini->exit_status = 126;
// 		else
// 			mini->exit_status = 127;
// 		return (ft_error(mini, NULL, strerror(errno)), -1);
// 	}
// 	if (stat(name, &statbuf) != 0)
// 		return (close(script), ft_error(mini, "Failed to stat file", NULL), -1);
// 	if (S_ISDIR(statbuf.st_mode))
// 	{
// 		close(script);
// 		mini->exit_status = 126;
// 		return (ft_error(mini, "Is a directory", NULL), -1);
// 	}
// 	*script_fd = script;
// 	return (0);
// }

