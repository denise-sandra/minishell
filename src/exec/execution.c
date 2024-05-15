/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/14 20:16:06 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execution(t_minishell *minishell)
{
     if (minishell->token[0]->type == TOKEN_SPECIAL_COMMAND)
          execute_special_command(minishell, minishell->token[0]->value);
     else if (minishell->token[0]->type == TOKEN_COMMAND)
          printf("not so special command\n");
     else
          printf("first token is not a command\n");
}