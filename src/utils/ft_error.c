/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:24:31 by derjavec          #+#    #+#             */
/*   Updated: 2024/06/06 16:34:01 by derjavec         ###   ########.fr       */
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

void check_malloc_error(t_minishell *mini, void *element, char *msg, int e)
{
     if (element == NULL)
	{
		ft_error(msg, mini);
		if (e > 0)
			exit(e);
	}
     return ; 
}
