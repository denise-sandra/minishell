/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/23 16:15:52 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tag_token(t_minishell *minishell)
{
	int		i;
	int		len;
	t_token	**token;

	i = 0;
	token = minishell->token;
	while (i < minishell->token_count)
	{
		len = ft_strlen(token[i]->value);
		printf("avant value: %s", token[i]->value);
		erase_quotes(minishell, i);
		if (len == 0)
			return ;
		else if (is_env_value(minishell, i) == 1)
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
		printf("apres value: %s type: %u\n", token[i]->value, token[i]->type);
		i++;
	}
}