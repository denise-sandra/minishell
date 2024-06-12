/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:35:41 by skanna            #+#    #+#             */
/*   Updated: 2024/06/12 19:02:51 by skanna           ###   ########.fr       */
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
	write(hd_pipe[1], line, line_len);
	free(line);
	return (0);
}

static void	read_here_doc(t_mini *mini, char *eof, int i)
{
	char	*line;
	int		is_eof;

	if (pipe(mini->here_fd) < 0)
		return (ft_error("Can't open infile", mini));
	is_eof = 0;
	while (is_eof == 0)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			is_eof = 1;
		else
			is_eof = process_here_line(mini->here_fd, line, eof);
	}
	close(mini->here_fd[1]);
	if (mini->fd_in && i < mini->cmd_count)
		mini->fd_in[i] = mini->here_fd[0];
	else
		close(mini->here_fd[0]);
}


static int	get_infile(t_mini *mini, t_token *token, int i)
{
	if (token->type == IN)
	{
		mini->fd_in[i] = open(token->next->value, O_RDONLY);
		if (mini->fd_in[i] < 0)
			return (ft_error("Can't open infile", mini), 1);
	}
	else if (token->type == HERE)
	{
		read_here_doc(mini, token->next->value, i);
		if (mini->error)
			return (1);
	}
	return (0);
}

static int	get_outfile(t_mini *mini, t_token *token, int i)
{
	if (token->type == OUT)
	{
		mini->fd_out[i] = open(token->next->value, O_CREAT
				| O_RDWR | O_TRUNC, 0644);
		if (mini->fd_out[i] < 0)
			return (ft_error("Can't open outfile", mini), 1);
	}
	if (token->type == APP)
	{
		mini->fd_out[i] = open(token->next->value, O_CREAT
				| O_RDWR | O_APPEND, 0644);
		if (mini->fd_out[i] < 0)
			return (ft_error("Can't open outfile", mini), 1);
	}
	return (0);
}

void	fill_fd(t_mini *mini)
{
	t_token	*tmp;
	int		i;

	tmp = mini->token;
	i = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		if (get_infile(mini, tmp, i) != 0)
			return ;
		if (get_outfile(mini, tmp, i) != 0)
			return ;
		tmp = tmp->next;
	}
}
