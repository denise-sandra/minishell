/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/21 10:40:55 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *join_path(t_minishell *minishell, t_token *token, char **paths, int i)
{
     char	*join_slash;
	char	*join_token;
	char	*tmp_value;

	join_token = NULL;
	tmp_value = malloc(ft_strlen(token->value) * sizeof(char));
	if (tmp_value == NULL)
		ft_error("Malloc in join_path", minishell);	
     join_slash = ft_strjoin(paths[i], "/");
	ft_strlcpy(tmp_value, token->value, ft_strlen(token->value) + 1);
	if (join_slash == NULL)
	{
		free_tab(paths);
		ft_error("Malloc in is_command", minishell);
	}
	tmp_value = erase_outer_quotes(tmp_value);
	if (token->value == NULL)
		ft_error("Malloc in join_path", minishell);
	join_token = ft_strjoin(join_slash, tmp_value);
	if (join_token == NULL)
	{
		free(join_slash);
		free_tab(paths);
		ft_error("Malloc in is_command", minishell);
	}
     free (join_slash);
	free(tmp_value);
     return (join_token);
}

int	is_normal_command(t_minishell *minishell, t_token *token)
{
	char	**paths;
	char	*path_with_token;
	int		i;

	paths = pars_path(minishell);
	if (!paths)
		ft_error("path spliting error", minishell);
	i = 0;
	while (paths[i])
	{
		path_with_token = join_path(minishell, token, paths, i);
		if (access(path_with_token, X_OK) == 0 && access(path_with_token, F_OK) == 0)
		{
			free(path_with_token);
			free_tab(paths);
			return (1);
		}	
		free(path_with_token);
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