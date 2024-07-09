/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/07/09 13:12:18 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_here_line(int *hd_pipe, char *line, const char *eof)
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

static int	read_here_doc(t_mini *mini, char *eof, int i)
{
	char	*line;
	int		is_eof;

	if (pipe(mini->here_fd) < 0)
		return (-1);
	is_eof = 0;
	while (is_eof == 0)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			is_eof = process_here_line(mini->here_fd, line, eof);
			if (is_eof == -1)
			{
				close(mini->here_fd[1]);
				close(mini->here_fd[0]);
				return (-1);
			}
		}
		else
			is_eof = 1;
	}
	close(mini->here_fd[1]);
	mini->fd_in[i] = mini->here_fd[0];
	return (0);

}

int	get_infile(t_mini *mini, t_token *token, int i)
{
	if (token->next && token->type == IN)
		mini->fd_in[i] = open(token->next->value, O_RDONLY);
	if (token->type == IN && mini->fd_in[i] < 0)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		mini->inv_fd[i] = 1;
	}
	else if (token->next && token->type == HERE)
	{
		if (read_here_doc(mini, token->next->value, i) != 0)
		{
			ft_putstr_fd("Error: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			mini->inv_fd[i] = 1;
		}
	}
	return (0);
}

void	get_outfile(t_mini *mini, t_token *token, int i)
{
	if (token->next && token->type == OUT)
		mini->fd_out[i] = open(token->next->value, O_CREAT
				| O_WRONLY | O_TRUNC, 0644);
	if (token->next && token->type == APP)
	{
		mini->fd_out[i] = open(token->next->value, O_CREAT
				| O_WRONLY | O_APPEND, 0644);
	}
	if ((token->type == OUT || token->type == APP) && \
		mini->fd_out[i] < 0)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		mini->inv_fd[i] = 1;
	}
}
