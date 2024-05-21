/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/05/21 11:19:57 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    echo_command(t_minishell *minishell)
{
    int i;
    t_token **token;

    i = 0;
    token = minishell->token;
    while (token[i])
    {
        if (token[i + 1] && ft_strncmp(token[i]->value, "echo", ft_strlen(token[i]->value)) == 0)
        {
            printf("%s\n", token[i + 1]->value);
            break ;
        }   
        else if (ft_strncmp(token[i]->value, "echo", ft_strlen(token[i]->value)) == 0)
        {
             printf("\n");
             break;
        }     
         i++;   
    }
}