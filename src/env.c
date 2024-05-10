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

char    *get_env_value(t_environement env, char *name)
{
     int  i;

     i = 0;
     while (i < env.count)
     {
          if (ft_strcmp(env.vars[i].name) == 0)
               return (env->vars[i].value);
          i++;
     }
     return (NULL);
}

void   env_fill_structure(char **envp)
{
     t_environement   env;
     char           **split_envp;
     
     env.count = 0;
     while (envp[env.count] && env.count < 100)
     {
          split_envp = ft_split_1st_token(envp[env.count], '=');            
          if (split_envp == NULL)
               ft_error("Malloc error in split");
          env.vars[env.count].name = split_envp[0];
          env.vars[env.count].value = split_envp[1];
          env.count++;
     }
}
