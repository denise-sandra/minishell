/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:25:43 by sandra            #+#    #+#             */
/*   Updated: 2024/08/01 16:26:59 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_here_line(int *hd_pipe, char *line, const char *eof)
{
	size_t	line_len;
	size_t	eof_len;

	line_len = ft_strlen(line);
	eof_len = ft_strlen(eof);
	if (line_len > 0 && line[line_len - 1] == '\n')
	{
		line[line_len - 1] = '\0';
		line_len--;
	}
	if (ft_strncmp(line, eof, eof_len) == 0 && line_len == eof_len)
		return (free(line), 1);
	line[line_len] = '\n';
	line_len++;
	if (write(hd_pipe[1], line, line_len) == -1)
		return (free(line), -1);
	free(line);
	return (0);
}
