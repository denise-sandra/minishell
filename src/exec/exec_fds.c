/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/13 13:59:48 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_line(t_mini *mini, char *line, char *eof,int i)
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
	write(mini->fd_in[i], line, line_len);
	free(line);
	return (0);
}

static int	get_infile(t_mini *mini, t_token *token, int i)
{
	int		is_eof;
	char	*line;
	char	*eof;
	
	is_eof = 0;
	eof = NULL;
	if (token->type == IN)
	{
		mini->fd_in[i] =  open(token->next->value, O_RDONLY);
		if (mini->fd_in[i] < 0)
			return (ft_error("Can't open infile", mini), 1);
	}
	else if (token->type == HERE)
	{
		eof = token->next->value;
		while (is_eof == 0)
		{
			line = readline(STDIN_FILENO);
			if (!line)
				is_eof = 1;
			else
				is_eof = process_line(mini, line, eof, i);
		}
	}
	return (0);
}

static int	get_outfile(t_mini *mini, t_token *token, int i)
{
	if (token->type == OUT)
	{
		mini->fd_out[i] =  open(token->next->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (mini->fd_out[i] < 0)
			return (ft_error("Can't open outfile", mini), 1);
	}
	if (token->type == APP)
	{
		mini->fd_out[i] =  open(token->next->value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (mini->fd_out[i] < 0)
			return (ft_error("Can't open outfile", mini), 1);
	}
	return (0);
}

int fill_fd(t_mini *mini)
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
			return (1);
		if (get_outfile(mini, tmp, i) != 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}