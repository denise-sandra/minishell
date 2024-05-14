/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:24:31 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/10 14:24:33 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void free_all(t_minishell *minishell)
{


     if (minishell.env->vars->name)
          free(minishell.env->vars->name);
     if (minishell.env->vars->value)
          free(minishell.env->vars->value);
     if (minishell.env->vars)
          free(minishell.env->vars);
     if (minishell->token->value)
          free(minishell->token->value);
     if (minishell->token)
          free(minishell->token);
     if (minishell->output_file)
          free(minishell->output_file);
     if (minishell->input_file)
          free(minishell->input_file);
     free(minishell);
}