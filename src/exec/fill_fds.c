/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/03 16:15:31 by derjavec         ###   ########.fr       */
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

static int	fill_fd_utils(t_mini *mini, int *in, int *out, t_token *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{
		i = check_pipes(tmp, i, in, out);
		if (tmp->type == IN || tmp->type == HERE)
		{
			if (mini->inv_fd[i] != 1 && get_infile(mini, tmp, i) != 0)
			{
				return (1);
				(*in)--;
				if (*in > 0 && mini->fd_in[i] > 1)
					close (mini->fd_in[i]);
			}
		}
		else if (tmp->type == OUT || tmp->type == APP)
		{
			if (mini->inv_fd[i] != 1)
			{
				get_outfile(mini, tmp, i);
				(*out)--;
				if (*out > 0 && mini->fd_out[i] > 1)
					close (mini->fd_out[i]);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	fill_fd(t_mini *mini)
{
	t_token	*tmp;
	int		in;
	int		out;

	tmp = mini->token;
	count_in_out(&in, &out, tmp);
	tmp = mini->token;
	if (fill_fd_utils(mini, &in, &out, tmp) != 0)
		return (1);
	return (0);
}
