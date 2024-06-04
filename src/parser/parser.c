/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/06/04 15:43:10 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_token	*create_token(char *value, t_type type, t_minishell *minishell)
// {
// 	t_token	*new_token;
	
// 	new_token = tok_new_node(value);
// 	if (new_token == NULL)
// 		ft_error("cant malloc when creating new token", minishell);
// 	new_token->type = type;
// 	new_token->sub_token = NULL;
// 	new_token->next = NULL;
// 	return (new_token);
// }

// char	*join_subtokens(t_token *sub, t_minishell *minishell)
// {
// 	char	*join;
// 	char	*temp;

// 	join = ft_strdup("");
// 	if (join == NULL)
// 		ft_error("cant malloc when duplicating sub tokens", minishell);
// 	while (sub && (sub->type == TEXT || sub->type == ENV))
// 	{
// 		temp = ft_strjoin(join, sub->value);
// 		if (temp == NULL)
// 		{
// 			free(join);
// 			ft_error("cant malloc when joining sub tokens", minishell);
// 		}
// 		free(join);
// 		join = temp;
// 		sub = sub->next;
// 	}
// 	return (join);
// }

// void	process_subtokens(t_token *sub, t_token **list, t_minishell *mini)
// {
// 	char	*join;
// 	t_token	*new_token;

// 	while (sub)
// 	{
// 		if (sub->type == TEXT || sub->type == ENV)
// 		{
// 			join = join_subtokens(sub, mini);
// 			if (*join)
// 			{
// 				new_token = create_token(join, TEXT, mini);
// 				tok_addback(list, new_token);
// 			}
// 			free(join);
// 			while (sub && (sub->type == TEXT || sub->type == ENV))
// 				sub = sub->next;
// 		}
// 		else
// 		{
// 			if (sub->type != OPEN_D_Q && sub->type != CLOSE_D_Q && \
// 				sub->type != OPEN_S_Q && sub->type != CLOSE_S_Q)
// 			{		
// 				new_token = create_token(sub->value, sub->type, mini);
// 				tok_addback(list, new_token);
// 			}
// 			sub = sub->next;
// 		}
// 	}
// }

// static t_token	*new_token_list(t_minishell *minishell)
// {
// 	t_token	*tmp;
// 	t_token	*new_list;

// 	tmp = minishell->token;
// 	new_list = NULL;
// 	while (tmp)
// 	{
// 		printf("tmp : %s\n", tmp->value);
// 		process_subtokens(tmp->sub_token, &new_list, minishell);
// 		tmp = tmp->next;
// 	}
// 	return (new_list);
// }

// void	parser(t_minishell *minishell)
// {
// 	t_token	*sub_token;
// 	t_token	*tmp;
// 	t_token	*old_list;

// 	tmp = minishell->token;
// 	old_list = minishell->token;
// 	while (tmp)
// 	{
// 		tmp->value = erase_extra_quotes(tmp->value, ft_strlen(tmp->value));
// 		if (tmp->value == NULL)
// 			ft_error("Malloc in erase_extra_quotes", minishell);
// 		printf("erase_extra_quotes: %s\n", tmp->value);
// 		sub_token = sub_token_in_nodes(minishell, tmp->value);
// 		expand_env(minishell, &sub_token);
// 		tmp->sub_token = sub_token;
// 		t_token *print = tmp->sub_token;
// 		while (print)
// 		{
// 			printf("parser subtoken2: %s  sub->type: %i\n", print->value, print->type);
// 			print = print->next;
// 		}
// 		tmp = tmp->next;
// 	}
// 	minishell->token = new_token_list(minishell);
// 	clean_token_list(old_list);
// 	t_token *print = minishell->token;
// 	while (print)
// 	{
// 		printf("new token value: %s, type: %d\n", print->value, print->type);
// 		print = print->next;
// 	}
// 	tag_token(minishell);
// }
