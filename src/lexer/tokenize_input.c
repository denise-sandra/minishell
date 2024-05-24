/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/24 14:34:15 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_token(t_minishell *minishell)
{
	int	i;

	minishell->token = malloc((minishell->token_count + 1) * sizeof(t_token *));
	if (minishell->token == NULL)
		ft_error("Malloc for minishell->token", minishell);
	i = 0;
	while (i < minishell->token_count)
	{
		minishell->token[i] = malloc(sizeof(t_token));
		if (minishell->token[i] == NULL)
			ft_error("Malloc for minishell->token[i]", minishell);
		ft_bzero(minishell->token[i], sizeof(t_token));
		i++;
	}
	minishell->token[i] = NULL;
}

static int	token_count(char **tokens)
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
}

static void	fill_token_struct(t_minishell *minishell, char **tokens)
{
	int	i;

	i = 0;
	while (i < minishell->token_count)
	{
		minishell->token[i]->value = malloc(((ft_strlen(tokens[i]) + 1)));
		if ((minishell->token[i]->value) == NULL)
		{
			free_tab(tokens);
			ft_error("Malloc error in tokenize_input", minishell);
		}
		ft_strlcpy(minishell->token[i]->value, tokens[i], \
		ft_strlen(tokens[i]) + 1);
		minishell->token[i]->order = i;
		i++;
	}
}

void	tokenize_input(char *input, t_minishell *minishell)
{
	char	**tokens;
	int		*quotes;

	quotes = check_quotes(input);
	if (quotes == NULL)
		ft_error("Malloc in check_quotes", minishell);
	if (quotes[0] % 2 != 0 || quotes[1] % 2 != 0)
		return;
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
	minishell->token_count = token_count(tokens);
	if (minishell->token_count == -1)
		return ;
	init_token(minishell);
	fill_token_struct(minishell, tokens);
	free_tab(tokens);
}
