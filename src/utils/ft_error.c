/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:24:31 by derjavec          #+#    #+#             */
/*   Updated: 2024/06/12 15:19:47 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *msg, t_mini *minishell)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (minishell->pretok)
		clean_pretokens(minishell);
	if (minishell->token)
		clean_token_list(&(minishell->token));
	if (minishell->fd_in)
	{
		free(minishell->fd_in);
		minishell->fd_in = NULL;
	}
	if (minishell->fd_out)
	{
		free(minishell->fd_out);
		minishell->fd_out = NULL;
	}
	if (minishell->pid)
	{
		free(minishell->pid);
		minishell->pid = NULL;
	}
	minishell->error = 1;
}

void	check_malloc_error(t_mini *mini, void *elem, char *msg, int e)
{
	if (elem == NULL)
	{
		ft_error(msg, mini);
		if (e > 0)
			exit(e);
	}
	return ;
}
