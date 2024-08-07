/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:24:31 by derjavec          #+#    #+#             */
/*   Updated: 2024/08/07 17:22:18 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cleanup(t_mini *minishell)
{
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
	if (minishell->tube)
	{
		free(minishell->tube);
		minishell->tube = NULL;
	}
}

void	ft_error(t_mini *minishell, char *msg, char *error_msg)
{
	if (error_msg != NULL)
		print_custom(error_msg);
	else
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	if (minishell != NULL)
		error_cleanup(minishell);
	minishell->error = 1;
}

void	print_custom(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
