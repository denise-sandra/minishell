/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/22 15:03:26 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	execution(t_minishell *minishell)
{
	if (minishell->token && minishell->token[0])
	{
		if (ft_strlen(minishell->token[0]->value) == 0)
			return ;
		else if (minishell->token[0]->type == TOKEN_ENV)
			printf("%s: command not found\n", minishell->token[0]->value);
		else if (minishell->token[0]->type == TOKEN_SPECIAL_COMMAND)
			execute_special_command(minishell, minishell->token[0]->value);
		else if (minishell->token[0]->type == TOKEN_COMMAND)
			printf("not so special command\n");
		else
			printf("%s: command not found\n", minishell->token[0]->value);
	}
}
