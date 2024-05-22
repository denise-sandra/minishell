/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/22 22:54:42 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_name_with_value(char *env_var, char *new_token, int j)
{
	int	i;

	i = 0;
	while (env_var[i])
	{
		new_token[j] = env_var[i];
		i++;
		j++;
	}
	return (j);
}

static char	*fill_new_token_utils(t_minishell *minishell, char *token, \
	int size, char **env_vars)
{
	char	*new_token;
	int		i;
	int		j;
	int		k;

	new_token = malloc((size + 1) * sizeof(char));
	if (new_token == NULL)
	{
		free(env_vars);
		ft_error("Malloc in fill_new_token", minishell);
	}
	i = 0;
	j = 0;
	k = 0;
	while (j < size)
	{
		if (token[i] == '$' && token[i+ 1])
		{
			j = replace_name_with_value(env_vars[k], new_token, j);
			i = i + env_name_len(token + i) + 1;
			k++;
		}
		else
			new_token[j++] = token[i++];
	}
	new_token[j] = '\0';
	return (new_token);
}

static char	**fill_env_vars(t_minishell *minishell, char **env_vars, \
			char *token, int count_env)
{
	char	*env_name;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (j < count_env)
	{
		while (token[i])
		{
			if (token[i] == '$' && token[i+ 1])
			{
				env_name = return_env_str(token + i);
				if (env_name == NULL)
				{
					free(env_vars);
					ft_error("Malloc in return_env_value", minishell);
				}
				env_vars[j++] = get_env_value(minishell->env, env_name);
				free(env_name);
				i++;
			}
			i++;
		}
	}
	env_vars[j] = NULL;
	return (env_vars);
}

char	*fill_new_token(t_minishell *minishell, char *token, int size)
{
	char	*new_token;
	char	**env_vars;
	int		count_env;

	count_env = count_env_var(token);
	env_vars = malloc ((count_env + 1) * sizeof(char *));
	if (env_vars == NULL)
		ft_error("Malloc in fill_new_token", minishell);
	env_vars = fill_env_vars(minishell, env_vars, token, count_env);
	new_token = fill_new_token_utils(minishell, token, size, env_vars);
	printf("%s\n", new_token);
	free(env_vars);
	return (new_token);
}