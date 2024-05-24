/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/25 00:04:57 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tag_token_utils(t_minishell *minishell, t_token	**token, int len, int i)
{	
	if (is_env_value(minishell, i) == 1)
		token[i]->type = TOKEN_ENV;
	else if (is_special_command(minishell, token[i]) == 1)
		token[i]->type = TOKEN_SPECIAL_COMMAND;
	else if (ft_strncmp(token[i]->value, "|", len) == 0)
		token[i]->type = TOKEN_OPS;
	else if (ft_strncmp(token[i]->value, ">", len) == 0)
		token[i]->type = TOKEN_REDIR_OUT;
	else if (ft_strncmp(token[i]->value, "<", len) == 0)
		token[i]->type = TOKEN_REDIR_IN;
	else if (ft_strncmp(token[i]->value, "EOF", len) == 0)
		token[i]->type = TOKEN_END;
	else if (is_normal_command(minishell, token[i]) == 1)
		token[i]->type = TOKEN_COMMAND;
	else
		token[i]->type = TOKEN_ARG;
}

void	tag_token(t_minishell *minishell)
{
	int		i;
	int		len;
	t_token	**token;

	i = 0;
	while (i < minishell->token_count)
	{
		printf("avant value: %s", minishell->token[i]->value);
		//minishell->token[i]->value = copy_inside_q(minishell->token[i]->value);
		erase_quotes(minishell, i);
		token = minishell->token;
		len = ft_strlen(token[i]->value);
		if (len == 0)
			return ;
		tag_token_utils(minishell, token, len, i);
		printf("apres value: %s type: %u\n", token[i]->value, token[i]->type);
		i++;
	}
}