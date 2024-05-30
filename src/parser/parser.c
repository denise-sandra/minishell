/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/30 17:55:32 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static t_token *new_token_list(t_minishell *minishell)
{
	t_token	*new_list;
	t_token	*last_token;
	t_token	*tmp;
	t_token	*sub_tmp;
	t_token	*new_token;
	char	*temp;

	new_list = NULL;
	last_token = NULL;
	tmp = minishell->token;
	while (tmp)
	{
		sub_tmp = tmp->sub_token;
		new_token = NULL;
		while (sub_tmp)
		{
			printf("Subtoken before: %s\n", sub_tmp->value);
			if (sub_tmp->type == OPEN_S_QUOTES || sub_tmp->type == CLOSE_S_QUOTES ||
				sub_tmp->type == OPEN_D_QUOTES || sub_tmp->type == CLOSE_D_QUOTES)
			{
				sub_tmp = sub_tmp->next;
				if (!sub_tmp)
					break ;
			}
			if (!new_token)
			{
				new_token = (t_token *)malloc(sizeof(t_token));
				if (!new_token)
					ft_error("Malloc in create_new_token_list", minishell);
				new_token->value = ft_strdup(sub_tmp->value);
				new_token->type = sub_tmp->type;
				new_token->sub_token = NULL;
				new_token->next = NULL;
			}
			else
			{
				temp = new_token->value;
				new_token->value = ft_strjoin(new_token->value, sub_tmp->value);
				free(temp);
				if (!new_token->value)
					ft_error("Malloc in ft_strjoin", minishell);
			}
			sub_tmp = sub_tmp->next;
		}
		if (new_token)
		{
			if (!new_list)
				new_list = new_token;
			else
				last_token->next = new_token;
			last_token = new_token;
		}
		tmp = tmp->next;
	}
	return (new_list);
}*/


// static t_token	*tokenize(t_minishell *mini)
// {
// 	t_token	*token;
// 	t_token	*sub_token;
// 	t_token	*tmp;
// 	char		*temp;
	
// 	token = mini->token;
// 	free (token->value);
// 	while (token)
// 	{
// 		token->value = NULL;
// 		sub_token = token->sub_token;
// 		while (sub_token)
// 		{
// 			int	i = 0;
// 			printf("vuelta numero: %d\n", i++);
// 			if (sub_token->type == OPEN_S_QUOTES || sub_token->type == CLOSE_S_QUOTES || \
// 				sub_token->type == OPEN_D_QUOTES | sub_token->type == CLOSE_D_QUOTES)
// 			{
// 				tmp = sub_token->next;
// 				if (tmp == NULL)
// 					tmp = token->next;
// 				ft_lstdelone_t(sub_token, free);
// 				sub_token = tmp;
// 			}
// 			else if (sub_token->type == SYMBOL)
// 			{
				
// 					token->value = ft_strdup(sub_token->value);
// 					printf("1ero: %s\n", token->value);
// 					if (token->value == NULL)
// 						ft_error("Malloc in ft_strdup", mini);
// 					if (sub_token->next)
// 					{
// 						tmp = token->next;
// 						token->next = sub_token->next;
// 						token->next->next = tmp;
// 						printf("%s\n", token->next->value);
						
// 					}
// 			}
// 			else if (sub_token->type == TEXT || sub_token->type == ENV || sub_token->type == OTHER)
// 			{
// 				if (token->value == NULL)
// 				{
// 					token->value = ft_strdup(sub_token->value);
// 					printf("1ero: %s\n", token->value);
// 					if (token->value == NULL)
// 						ft_error("Malloc in ft_strdup", mini);
// 				}	
// 				else
// 				{
// 					temp = token->value;
// 					printf("temp: %s\n", temp);
// 					token->value = ft_strjoin(token->value, sub_token->value);
// 					free(temp);
// 					if (token->value == NULL)
// 						ft_error("Malloc in ft_strjoin", mini);
// 					printf("segundo: %s\n", token->value);
// 				}
					
// 			}
// 			sub_token = sub_token->next;
// 		}
// 		token = token->next;
// 	}
// 	//funion que borre todos los subtokens
// 	return (token);
// }

static t_token *new_token_list(t_minishell *minishell)
{
	t_token *tmp;
	t_token *new_list;

	tmp = minishell->token;
	new_list = NULL;
	while (tmp)
	{
		while (tmp->sub_token)
		{
			new_token = tmp->sub_token;
		}
		tmp = tmp->next;
	}
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
		// printf("erase_extra_quotes: %s\n", tmp->value);
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
		
		// t_token    *pnt;
		// pnt = tmp->sub_token;
		// while (pnt)
		// {
		// 	printf("list st: %s  subtype: %u\n", pnt->value, pnt->type);
		// 	pnt = pnt->next;
		// }
		//tmp = new_token_list(tmp);
		tmp = tmp->next;
	}
	
	t_token *print = minishell->token;
	while (print)
	{
		printf("new token value: %s, type: %d\n", print->value, print->type);
		print = print->next;
	}
	new_token_list(minishell);
	tag_token(minishell);
}
