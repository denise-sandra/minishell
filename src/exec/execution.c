/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/29 12:12:36 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_minishell *minishell)
{
	t_token *tmp;

	tmp = minishell->token;
	
	if (tmp && tmp->value)
	{
		if (ft_strlen(tmp->value) == 0)
			return ;
		else if (tmp->type == ENV)
			printf("%s: command not found\n", tmp->value);
		else if (tmp->type == BUILTIN)
			execute_builtin(minishell, tmp->value);
		else if (tmp->type == COMMAND)
			printf("not so special command\n");
		else
			printf("%s: command not found\n", tmp->value);
	}
}
