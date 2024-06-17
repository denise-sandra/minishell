/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/06/17 14:32:32 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_command(t_mini *mini, int i)
{
	t_token *tmp;
	int j;

	j = 0;
	tmp = mini->token;
	while (i != 0 && tmp && j <= i)
	{
		tmp = tmp->next;
		j++;
	}
	if (tmp->cmd_tab[1])
		printf("%s\n", tmp->cmd_tab[1]);
	else
		printf("\n");
}
