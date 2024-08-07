/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/08/07 16:49:28 by derjavec         ###   ########.fr       */
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

	if (pipe(mini->here_fd) < 0)
		return (-1);
	is_eof = 0;
	while (is_eof == 0)
	{
		sigs_here();
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (handle_sig_int(mini) != 0)
			return (-2);
		// check_sigs(mini);
		// printf("exit: %d\n", mini->exit_status);
		// if (mini->exit_status == 130)
		// 	return (-2);
		if (line)
		{
			if (ft_eof(mini, eof, line, &is_eof) != 0)
				return (-1);
		}
		else
			is_eof = 1;
	}
	close_here_fd(mini);
	mini->fd_in[i] = mini->here_fd[0];
	return (0);
}

char	*get_infile(t_mini *mini, t_token *token, int i, char *msg)
{
	int	res;

	if (token->type == IN && mini->inv_fd[i] == 1)
		return (msg);
	if (token->next && token->type == IN)
		mini->fd_in[i] = open(token->next->value, O_RDONLY);
	if (token->type == IN && mini->fd_in[i] < 0)
	{
		msg = strdup(strerror(errno));
		mini->inv_fd[i] = 1;
	}
	else if (token->next && token->type == HERE)
	{
		res = read_here_doc(mini, token->next->value, i);
		if (res == -1)
		{
			ft_putstr_fd("Error: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			mini->inv_fd[i] = 1;
		}
		else if (res == -2)
			mini->error = 1;
	}
	return (msg);
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
