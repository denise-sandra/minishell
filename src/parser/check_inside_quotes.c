/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inside_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/25 00:00:10 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *copy_inside_q(char *str)
{
    char    *new_str;
    int q_type;
    int i;
    int j;
    int q;
    
    if (str[0] != 39 || str[0] != 34)
        return (str);
    q_type = str[0];
    i = 1;
    j = 0;
    q = 0;
    while (str[i])
    {
        while (q == 0)
        {
           new_str[j++] = str[i++];
           if (str[i] == q_type)
                q = !q;
        }
        i++;
        if (str[i] == q_type)
                q = !q;
    }
}