/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/08/02 13:03:00 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	ft_eof(t_mini *mini, char *eof, char *line, int *is_eof)
{
	*is_eof = process_here_line(mini->here_fd, line, eof);
	if (*is_eof == -1)
	{
		close(mini->here_fd[1]);
		close(mini->here_fd[0]);
		return (-1);
	}
	return (0);
}

static int	read_here_doc(t_mini *mini, char *eof, int i)
{
	char	*line;
	int		is_eof;
	void (*prev_sigquit)(int);

	if (pipe(mini->here_fd) < 0)
		return (-1);
	is_eof = 0;
	while (is_eof == 0)
	{
		prev_sigquit = signal(SIGQUIT, SIG_IGN);
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			if (ft_eof(mini, eof, line, &is_eof) != 0)
			{
				// signal(SIGQUIT, prev_sigquit);
				return (-1);
			}
		}
		else
			is_eof = 1;
	}
	close(mini->here_fd[1]);
	mini->fd_in[i] = mini->here_fd[0];
	// signal(SIGQUIT, prev_sigquit);
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
	{
		mini->fd_out[i] = open(token->next->value, O_CREAT
				| O_WRONLY | O_TRUNC, 0644);
	}
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
