/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/28 14:43:35 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	init_token(t_minishell *minishell)
{
	minishell->token = malloc(sizeof(t_token));
	if (minishell->token == NULL)
		ft_error("Malloc for minishell->token", minishell);
	*(minishell->token) = NULL;
}*/

/*static int	token_count(char **tokens)
{
	int	i;

	i = 0;
	if (tokens[i] == NULL)
	{
		free_tab(tokens);
		return (-1);
	}
	while (tokens[i])
		i++;
	return (i);
}*/


static t_token	*fill_token_struct(t_minishell *minishell, char **tokens)
{
	t_token	*new_node;
	t_token	*lst_token;
	int	i;

	i = 0;
	lst_token = NULL;
	while (tokens[i])
	{
		new_node = ft_lstnew_t(tokens[i]);
		if (new_node == NULL)
		{
			free_tab(tokens);
			ft_error("Malloc in fill_new_structure", minishell);
		}
		ft_lstadd_back_t(&lst_token, new_node);
	}
	return (lst_token);
}

void	tokenize_input(char *input, t_minishell *minishell)
{
	char	**tokens;
	int		*quotes;

	quotes = check_quotes(input);
	if (quotes == NULL)
		ft_error("Malloc in check_quotes", minishell);
	tokens = ft_split_quotes(input, 32, quotes);
	if (tokens == NULL)
	{
		free(quotes);
		ft_error("Malloc split_input", minishell);
	}
	int i = 0;
	while (tokens[i])
		printf("split : %s\n", tokens[i++]);
	free(quotes);
	/*minishell->token_count = token_count(tokens);
	if (minishell->token_count == -1)
		return ;*/
	//init_token(minishell);
	minishell->token = fill_token_struct(minishell, tokens);
	free_tab(tokens);
}
