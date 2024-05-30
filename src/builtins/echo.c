/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/05/30 12:06:09 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    echo_command(t_minishell *minishell)
{
	// int i;
	t_token *tmp;

	// i = 0;
	tmp = minishell->token;
	while (tmp)
	{
		if (tmp->next && ft_strncmp(tmp->value, "echo", ft_strlen(tmp->value)) == 0)
		{
			printf("%s\n", tmp->next->value);
			break ;
		}   
		else if (ft_strncmp(tmp->value, "echo", ft_strlen(tmp->value)) == 0)
		{
			 printf("\n");
			 break;
		}    
		tmp = tmp->next; 
		// i++;   
	}
}