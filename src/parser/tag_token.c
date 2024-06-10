/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/06/10 13:16:26 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_normal_command(t_minishell *minishell, t_token *token)
// {
// 	char	**paths;
// 	char	*path_with_token;
// 	int		i;

// 	paths = pars_path(minishell);
// 	if (!paths)
// 		ft_error("path spliting error", minishell);
// 	i = 0;
// 	while (paths[i])
// 	{
// 		path_with_token = join_path(minishell, token, paths, i);
// 		if (access(path_with_token, X_OK) == 0 && \
// 			access(path_with_token, F_OK) == 0)
// 		{
// 			free(path_with_token);
// 			free_tab(paths);
// 			return (1);
// 		}	
// 		free(path_with_token);
// 		i++;
// 	}
// 	free_tab(paths);
// 	return (0);
// }

static int	is_builtin(t_minishell *minishell, t_token *token)
{
	int	i;
	size_t	len;
	
	len = ft_strlen(token->value);
	i = 0;
	while (i < 6)
	{
		if (ft_strlen(minishell->builtin[i]) == len)
		{
			if (ft_strncmp(token->value, minishell->builtin[i], len) == 0)
			return (1);
		}
		i++;
	}
	return (0);
}

static void	tag_token_utils(t_minishell *minishell, t_token	*token)
{	
	if (token->next && token->type == HEREDOC)
		token->next->type = END;	
	else if (token->next && (token->type == OUT || token->type == APPEND))
		token->next->type = OUT_FILE;
	else if (token->next && token->type == IN)
		token->next->type = IN_FILE;
	else if ((token->order == 0 && token->type == TEXT) || token->prev == PIPE || token->prev == IN_FILE)
	{
		if (is_builtin(minishell, token) == 1)
			token->type = BUILTIN;
		else
			token->type = COMMAND;
	}
	else if (token->value[0] == '-')
		token->type = OPT;
	else if (token->type == TEXT)
		token->type = ARG;
}

void	tag_token(t_minishell *minishell)
{
	t_token	*tmp;
	int		i;

	tmp = minishell->token;
	i = 0;
	while (tmp)
	{
		tmp->order = i;
		if (tmp->type != END && tmp->type != OUT_FILE && tmp->type != IN_FILE)
			tag_token_utils(minishell, tmp);
		printf("value: %s type: %u prev_type: %u\n", tmp->value, tmp->type, tmp->prev);
		i++;
		if (tmp->next)
		tmp->next->prev = tmp->type;
		tmp = tmp->next;
	}
}