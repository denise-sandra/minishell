/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/15 14:46:38 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export(t_minishell *minishell)
{
     int  res;
     t_lst_env *new_node;
     t_lst_env *temp;
     char **split_new_envp;

     new_node = NULL;
     temp = NULL;
     res = 0;
     if (minishell->token[1])
          res = ft_strchr_int(minishell->token[1]->value, '=');
     else
     {
          temp = minishell->env;
          while(temp)
          {
               printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
               temp = temp->next;
          }
     }
     if (res == 1)
     {
          split_new_envp = ft_split_1st_token(minishell->token[1]->value, '=');
          if (split_new_envp == NULL)
               ft_error("Malloc in export function", minishell);
          new_node = ft_new_node(split_new_envp[0], split_new_envp[1]);
          if (new_node == NULL)
               ft_error("Malloc in export function", minishell);
          ft_add_back(&minishell->env, new_node);
     }
     else if (res == 2)
          printf("bash: export: `=': not a valid identifier\n");
}