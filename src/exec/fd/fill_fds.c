/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/08/05 15:20:08 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_in_out(int *in, int *out, t_token *tmp)
{
	*in = 0;
	*out = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == IN)
			(*in)++;
		if (tmp->type == OUT)
			(*out)++;
		tmp = tmp->next;
	}
}

static int	check_pipes(t_token *tmp, int i, int *in, int *out)
{
	if (tmp->type == PIPE)
	{
		count_in_out(in, out, tmp->next);
		i++;
	}
	return (i);
}

static void	redir_out(t_mini *mini, int *out, t_token *tmp, int i)
{
	if (mini->inv_fd[i] != 1)
	{
		get_outfile(mini, tmp, i);
		(*out)--;
		if (*out > 0 && mini->fd_out[i] > 1)
			close (mini->fd_out[i]);
	}
}

static void	fill_fd_utils(t_mini *mini, int *in, int *out, char **msg)
{
	int		i;
	t_token	*tmp;

	tmp = mini->token;
	i = 0;
	while (tmp)
	{
		i = check_pipes(tmp, i, in, out);
		if (tmp->type == IN || tmp->type == HERE)
		{
			msg[i] = get_infile(mini, tmp, i, msg[i]);
			if (mini->inv_fd[i] != 0 || mini->error != 0)
			{
				(*in)--;
				if (*in > 0 && mini->fd_in[i] > 2)
					close (mini->fd_in[i]);
			}
		}
		else if (tmp->type == OUT || tmp->type == APP)
			redir_out(mini, out, tmp, i);
		tmp = tmp->next;
	}
	return ;
}

void	fill_fd(t_mini *mini, t_token *tmp)
{
	int		in;
	int		out;
	int		i;
	char	**msg;

	msg = malloc((mini->pipe_count + 1) * sizeof(char *));
	if (!msg)
		return (ft_error(mini, NULL, strerror(errno)));
	init_tab(msg, mini->pipe_count);
	count_in_out(&in, &out, tmp);
	fill_fd_utils(mini, &in, &out, msg);
	i = 0;
	while (i < mini->pipe_count)
	{
		if (mini->inv_fd[i] != 0)
		{
			ft_putstr_fd("Error: ", 2);
			ft_putstr_fd(msg[i], 2);
			ft_putstr_fd("\n", 2);
			free (msg[i]);
		}
		i++;
	}
	free(msg);
}
