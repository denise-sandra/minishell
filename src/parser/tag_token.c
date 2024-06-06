/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/06/06 17:53:37 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(t_minishell *minishell, t_token *token)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(token->value, minishell->builtin[i], \
			ft_strlen(token->value)) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	tag_token_utils(t_minishell *minishell, t_token	*token, int len)
{
	if (is_builtin(minishell, token) == 1)
		token->type = BUILTIN;
	else if (token->type ==HEREDOC)
		token->next->type = END;
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
		printf("value: %s type: %u\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
}