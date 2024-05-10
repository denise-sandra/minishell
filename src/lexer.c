/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/10 15:45:26 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_token(t_minishell *minishell)
{
	int i;

	minishell->token = malloc((minishell->token_count) * sizeof(t_token *));
	if (minishell->token == NULL)
		ft_error("Malloc for minishell->token", minishell);
	i = 0;
	while (i < minishell->token_count)
	{
		minishell->token[i] = malloc(sizeof(t_token *));
		if (minishell->token[i] == NULL)
			ft_error("Malloc for minishell->token[i]", minishell);
		ft_bzero(minishell->token[i], sizeof(t_token));
		i++;
	}
}

void	tokenize_input(char *input, t_minishell *minishell)
{
	char **split_input;
	int  i;

	split_input = split_quotes(input, ' ');
	if (split_input == NULL)
		ft_error("Malloc split_input", minishell);
	i = 0;
	while (split_input[i])
	{
		printf("split: %s\n", split_input[i]);
		i++;
	}
	minishell->token_count = i;
	init_token(minishell);
	printf("test\n");
	i = 0;
	while (i < minishell->token_count)
	{
		minishell->token[i]->value = split_input[i];
		minishell->token[i]->order = i;
		i++;
	}
}