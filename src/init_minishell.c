/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:53:57 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/10 16:53:58 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_minishell *init_minishell(char **envp)
{
     t_minishell *minishell;

     minishell = malloc(sizeof(t_minishell));
     if (minishell == NULL)
          ft_error("Malloc for minishell structure", minishell);
     ft_bzero(minishell, sizeof(minishell));
     minishell->env = env_fill_structure(envp, minishell);
     return (minishell);
}
