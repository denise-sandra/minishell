/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/15 16:52:06 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(t_minishell *minishell, t_token *token)
{
	char	**paths;
	char	*path_join_1;
	char	*path_join_2;
	int		i;

	paths = pars_path(minishell);
	if (!paths)
		ft_error("path spliting error", minishell);
	i = 0;
	while (paths[i])
	{
		path_join_1 = ft_strjoin(paths[i], "/");
		if (path_join_1 == NULL)
		{
			free_tab(paths);
			ft_error("Malloc in is_command", minishell);
		}
		path_join_2 = ft_strjoin(path_join_1, token->value);
		if (path_join_2 == NULL)
		{
			free(path_join_1);
			free_tab(paths);
			ft_error("Malloc in is_command", minishell);
		}	
		if (access(path_join_2, X_OK) == 0 && access(path_join_2, F_OK) == 0)
		{
			free(path_join_1);
			free(path_join_2);
			free_tab(paths);
			return (1);
		}	
		free(path_join_1);
		free(path_join_2);
		i++;
	}
	free_tab(paths);
	return (0);
}

int	is_special_command(t_minishell *minishell, t_token *token)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (ft_strncmp(token->value, minishell->special_commands[i], ft_strlen(token->value)) == 0)
			return (1);
		i++;
	}
	return (0);
}


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
		else if (is_command(minishell, token[i]) == 1)
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
	split_input = ft_split(input, 32, special_c);
	if (split_input == NULL)
		ft_error("Malloc split_input", minishell);
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
