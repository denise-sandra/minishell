/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/06/03 14:50:25 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tag_token_utils(t_minishell *minishell, t_token	*token, int len)
{	
	if (is_builtin(minishell, token) == 1)
		token->type = BUILTIN;
	else if (ft_strncmp(token->value, "|", len) == 0)
		token->type = OPS;
	else if (ft_strncmp(token->value, ">", len) == 0)
		token->type = REDIR_OUT;
	else if (ft_strncmp(token->value, "<", len) == 0)
		token->type = REDIR_IN;
	else if (ft_strncmp(token->value, ">>", len) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->value, "<<", len) == 0)
	{
		token->type = HEREDOC;
		printf("%s\n", token->next->value);
		if (token->next && (token->next->type == TEXT || token->next->type == OTHER))
			token->next->type = END;
	}	
	else if (is_normal_command(minishell, token) == 1)
		token->type = COMMAND;
	else
		token->type = ARG;
}

void	tag_token(t_minishell *minishell)
{
	t_token	*tmp;
	int		len;

	tmp = minishell->token;
	while (tmp)
	{
		if (tmp->type != END)
		{
			len = ft_strlen(tmp->value);
			if (len == 0)
				return ;
			tag_token_utils(minishell, tmp, len);
		}
		printf("apres value: %s type: %u\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
}