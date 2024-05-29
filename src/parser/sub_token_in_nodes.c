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

static void analyse_node(t_lst_token *node, int len)
{
	static int sq = 0;
	static int dq = 0;
	// revisar los pipe y dir
	if (sq % 2 == 0 && ft_strchr_int(node->value, '$') == 1)
		node->sub_type = ENV;
	else if (len == 1 && node->value[0] == 39)
	{
		node->sub_type = OPEN_S_QUOTES;
		sq++;
	}		
	else if (len == 1 && node->value[0] == 34)
	{
		node->sub_type = OPEN_D_QUOTES;
		dq++;
	}	
	else if (dq % 2 != 0 && len == 2 && node->value[0] == 34)
	{
		node->sub_type = CLOSE_D_QUOTES;
		dq++;
	}	
	else if (sq % 2 != 0 && len == 2 && node->value[0] == 39)
	{
		node->sub_type = CLOSE_S_QUOTES;
		sq++;
	}	
	else if (len == 1 && (node->value[0] == '|'|| node->value[0] == '>' || node->value[0] == '<'))
		node->sub_type = SYMBOL;
	else if ((dq !=0 && dq % 2 != 0) || (sq != 0 && sq % 2 != 0))
		node->sub_type = TEXT;
}

static t_lst_token **create_node(t_minishell *minishell, char *str, \
	int i, t_lst_token **sub_token)
{
	char    *split_str;
	t_lst_token *node;
	
	split_str = malloc((i + 1) * sizeof(char));
	if (split_str == NULL)
	{
		ft_lstclear_st(sub_token, free);
		ft_error("Malloc in create_node", minishell);
	}
	ft_strlcpy(split_str, str, i + 1);
	node = ft_lstnew_st(split_str);
	if (node == NULL)
	{
		ft_lstclear_st(sub_token, free);
		ft_error("Malloc in create_node", minishell);
	}
	free(split_str);
	analyse_node(node, ft_strlen(node->value));
	printf("sub_token value: %s sub_type: %u\n", node->value, node->sub_type);
	ft_lstadd_back_st(sub_token, node);
	return (sub_token);
}

// no estamos tratando las opciones todavia
t_lst_token    **sub_token_in_nodes(t_minishell *minishell, char *str)
{
	t_lst_token    **sub_token;
	int i;
	
	sub_token = malloc(sizeof(t_lst_token*));
	if (sub_token == NULL)
		ft_error("Malloc in sub_token_in_nodes", minishell);
	*sub_token = NULL;
	while (str[0])
	{
		i = 0;
		if (str[i] == 34 || str[i] == 39 || \
			str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			while (str[i] == str[0])
				i++;
		}
		else if(str[i] == '$')
			i = env_name_len(str) + 1;		
		else
		{
			while (str[i] && str[i] != 39 && str
			[i] != 34 && str[i] != '|' \
				&& str[i] != '>' && str[i] != '<' && str[i] != '$')
				i++;
		}
		sub_token = create_node(minishell, str, i, sub_token);
		str = str + i;
	}
	return (sub_token);
}
