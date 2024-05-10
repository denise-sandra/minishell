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
     int  len;

     len = ft_strlen(name);
     i = 0;
     while (i < env.count)
     {
          if (ft_strncmp(env.vars[i].name, name, len) == 0)
               return (env.vars[i].value);
          i++;
     }
     return (NULL);
}

t_environement   env_fill_structure(char **envp, t_minishell *minishell)
{
     t_environement   env;
     char           **split_envp;
     int            i;

     i = 0;
     while (envp[i])
          i++;
     env.vars = malloc((i + 1) * sizeof(t_env_var));
     if (env.vars == NULL)
          ft_error("Malloc in env.vars", minishell);
     env.count = 0;
     while (envp[env.count] && env.count < 100)
     {
          split_envp = ft_split_1st_token(envp[env.count], '=');            
          if (split_envp == NULL)
               ft_error("Malloc error in split", minishell);
          env.vars[env.count].name = split_envp[0];
          env.vars[env.count].value = split_envp[1];
          env.count++;
     }
     env.vars[env.count].name = NULL;
     env.vars[env.count].value = NULL;
     return(env);
}
