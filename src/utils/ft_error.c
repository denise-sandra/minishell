/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:24:31 by derjavec          #+#    #+#             */
/*   Updated: 2024/06/05 00:22:59 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *msg, t_minishell *minishell)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (minishell->pretok)
		clean_pretokens(minishell);
	if (minishell->token)
		clean_token_list(minishell->token);
}

// void	ft_error(char *msg, t_minishell *minishell)
// {
// 	write(2, msg, ft_strlen(msg));
// 	write(2, "\n", 1);
// }
