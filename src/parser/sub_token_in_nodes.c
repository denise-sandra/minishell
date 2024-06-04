/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_token_in_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/28 15:14:08 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void analyse_node(t_token *node, int len)
// {
// 	static int sq = 0;
// 	static int dq = 0;
// 	// revisar los pipe y dir
// 	if (sq % 2 == 0 && ft_strchr_int(node->value, '$') >= 0)
// 		node->type = ENV;
// 	else if (len == 1 && node->value[0] == 39)
// 	{
// 		node->type = OPEN_S_Q;
// 		sq++;
// 	}		
// 	else if (len == 1 && node->value[0] == 34)
// 	{
// 		node->type = OPEN_D_Q;
// 		dq++;
// 	}	
// 	else if (dq % 2 != 0 && len == 2 && node->value[0] == 34)
// 	{
// 		node->type = CLOSE_D_Q;
// 		dq++;
// 	}	
// 	else if (sq % 2 != 0 && len == 2 && node->value[0] == 39)
// 	{
// 		node->type = CLOSE_S_Q;
// 		sq++;
// 	}	
// 	else if (len == 1 && (node->value[0] == '|'|| node->value[0] == '>' || node->value[0] == '<'))
// 		node->type = SYMBOL;
// 	else if ((dq != 0 && dq % 2 != 0) || (sq != 0 && sq % 2 != 0))
// 		node->type = TEXT;
// }

// static t_token	*create_node(t_minishell *minishell, char *str, \
// 	int i, t_token *sub_token)
// {
// 	char    *split_str;
// 	t_token *node;

// 	split_str = malloc((i + 1) * sizeof(char));
// 	if (split_str == NULL)
// 	{
// 		clean_token_list(sub_token);
// 		ft_error("Malloc in create_node", minishell);
// 	}
// 	ft_strlcpy(split_str, str, i + 1);
// 	node = tok_new_node(split_str);
// 	if (node == NULL)
// 	{
// 		free(split_str);
// 		clean_token_list(sub_token);
// 		ft_error("Malloc in create_node", minishell);
// 	}
// 	free(split_str);
// 	analyse_node(node, ft_strlen(node->value));
// 	// printf("sub_token value: %s type: %u\n", node->value, node->type);
// 	tok_addback(&sub_token, node);
// 	return (sub_token);
// }

// // no estamos tratando las opciones todavia
// t_token	*sub_token_in_nodes(t_minishell *minishell, char *str)
// {
// 	t_token	*sub_token;
// 	int		i;

// 	//sub_token = malloc(sizeof(t_token *));
// 	//if (sub_token == NULL)
// 		//ft_error("Malloc in sub_token_in_nodes", minishell);
// 	sub_token = NULL;
// 	while (str[0])
// 	{
// 		i = 0;
// 		if (str[i] == 34 || str[i] == 39 || \
// 			str[i] == '|' || str[i] == '>' || str[i] == '<')
// 		{
// 			while (str[i] == str[0])
// 				i++;
// 		}
// 		else
// 		{
// 			while (str[i] && str[i] != 39 && str
// 				[i] != 34 && str[i] != '|' \
// 				&& str[i] != '>' && str[i] != '<')
// 				i++;
// 		}
// 		sub_token = create_node(minishell, str, i, sub_token);
// 		str = str + i;
// 	}
// 	return (sub_token);
// }
