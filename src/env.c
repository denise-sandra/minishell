/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/08 18:46:11 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

Environement   init_env(char **envp)
{
     Environement   env;
     int            i;
     
     env.count = 0;
     i = 0;
     while (envp[i] && env.count < 100)
     {
          //split hasta = y poner en nombre y el resto en valor.
     }
}