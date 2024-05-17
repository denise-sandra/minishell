/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/17 11:36:26 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tag_token(t_minishell *minishell)
{
	int		i;
	int		len;
	t_token	**token;

	i = 0;
	token = minishell->token;
	while (i < minishell->token_count)
	{
		len = ft_strlen(token[i]->value);
		if (token[i]->value[0] == '$')
			token[i]->type = TOKEN_ENV;
		else if (is_special_command(minishell, token[i]) == 1)
			token[i]->type = TOKEN_SPECIAL_COMMAND;
		else if (ft_strncmp(token[i]->value, "|", len) == 0)
			token[i]->type = TOKEN_OPS;
		else if (ft_strncmp(token[i]->value, ">", len) == 0)
			token[i]->type = TOKEN_REDIR_OUT;
		else if (ft_strncmp(token[i]->value, "<", len) == 0)
			token[i]->type = TOKEN_REDIR_IN;
		else if (ft_strncmp(token[i]->value, "EOF", len) == 0)
			token[i]->type = TOKEN_END;
		else if (is_normal_command(minishell, token[i]) == 1)
			token[i]->type = TOKEN_COMMAND;
		else
			token[i]->type = TOKEN_ARG;
		i++;
	}
}

void	init_token(t_minishell *minishell)
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
}

void	tokenize_input(char *input, t_minishell *minishell)
{
	char	**split_input;
	char	special_c[3];
	int		i;

	special_c[0] = '\'';
	special_c[1] = '\"';
	special_c[2] = '\0';
	if (check_if_closed_quotes(input) == 0)
		return ;
	split_input = ft_split(input, 32, special_c);
	if (split_input == NULL)
		ft_error("Malloc split_input", minishell);
	/*i = 0;
	while (split_input[i])
		printf("split %s\n", split_input[i++]);*/
	i = 0;
	while (split_input[i])
		i++;
	minishell->token_count = i;
	init_token(minishell);
	i = 0;
	while (i < minishell->token_count)
	{
		minishell->token[i]->value = malloc(((ft_strlen(split_input[i]) + 1)));
		if ((minishell->token[i]->value) == NULL)
		{
			free_tab(split_input);
			ft_error("Malloc error in tokenize_input", minishell);
		}
		ft_strlcpy(minishell->token[i]->value, split_input[i], ft_strlen(split_input[i]) + 1);
		minishell->token[i]->order = i;
		i++;
	}
	minishell->token[minishell->token_count] = NULL;
	free_tab(split_input);
	tag_token(minishell);
}
