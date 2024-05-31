/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/31 09:28:03 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token *new_token_list(t_minishell *minishell)
{
	t_token *tmp;
	t_token *new_list;
	t_token *first;
	int	i;

	tmp = minishell->token;
	new_list = NULL;
	first = NULL;
	i = 0;
	while (tmp)
	{
		while (tmp->sub_token)
		{
			if (tmp->sub_token->type != OPEN_D_QUOTES  && tmp->sub_token->type != OPEN_S_QUOTES \
			&& tmp->sub_token->type != CLOSE_D_QUOTES && tmp->sub_token->type != CLOSE_S_QUOTES )
			{
				new_list = ft_lstnew_t(ft_strdup(tmp->sub_token->value));
				if (new_list == NULL)
					ft_error("Malloc in new_token_list", minishell);
				new_list->type = tmp->sub_token->type;
				if (i == 0)
					first = new_list;
				new_list = new_list->next;
				clean_token(tmp->sub_token);
				i++;
			}
			tmp->sub_token = tmp->sub_token->next;	
		}
		printf("new token value1: %s, type: %d\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
	clean_token(tmp);
	// t_token *print = first;
	// while (print)
	// {
	// 	printf("new token value1: %s, type: %d\n", print->value, print->type);
	// 	print = print->next;
	// }
	return (first);
}

void	parser(t_minishell *minishell)
{
	t_token	*sub_token;
	t_token	*tmp;

	tmp = minishell->token;
	while (tmp)
	{
		tmp->value = erase_extra_quotes(tmp->value, ft_strlen(tmp->value));
		if (tmp->value == NULL)
			ft_error("Malloc in erase_extra_quotes", minishell);
		printf("erase_extra_quotes: %s\n", tmp->value);
		sub_token = *sub_token_in_nodes(minishell, tmp->value);
		t_token *lale= sub_token;
		while (lale)
		{
			printf("parser subtoken 1: %s\n", lale->value);
			lale = lale->next;
		}
		expand_env(minishell, &sub_token);
		minishell->token->sub_token = sub_token;
		t_token *lala= minishell->token->sub_token;
		while (lala)
		{
			printf("parser subtoken 2: %s\n", lala->value);
			lala = lala->next;
		}
		tmp = tmp->next;
	}
	minishell->token = new_token_list(minishell);
	t_token *print = minishell->token;
	while (print)
	{
		printf("new token value2: %s, type: %d\n", print->value, print->type);
		print = print->next;
	}
	tag_token(minishell);
}
