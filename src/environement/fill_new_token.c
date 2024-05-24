/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/24 15:12:21 by deniseerjav      ###   ########.fr       */
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



static char	*fill_new_token(t_minishell *minishell, char *token, \
	int size, char **env_vars)
{
	char	*new_token;
	int		i;
	int		j;
	int		k;
	int		q;

	new_token = malloc((size + 1) * sizeof(char));
	if (new_token == NULL)
	{
		free(env_vars);
		ft_error("Malloc in fill_new_token", minishell);
	}
	i = 0;
	j = 0;
	k = 0;
	q = 0;
	while (j < size)
	{
		if (token[i] == 39)
			q++;
		if (token[i] == '$' && token[i + 1] && q % 2 == 0)
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

static	int	fill_vars_utils(t_minishell *minishell, char *token, char **env_vars, int j)
{
	char	*env_name;
	int		s_q;
	int		d_q;
	int		i;
	
	s_q = 0;
	d_q = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == 34)
			d_q++;
		if (token[i] == 39)
			s_q++;
		if (token[i] == '$' && token[i + 1] && (s_q % 2 == 0 || d_q % 2 != 0))
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
	return (j);
}

static char	**fill_vars(t_minishell *minishell, char **env_vars, char *token, int env)
{
	int		i;
	
	i = 0;
	while (i < env)
		i = fill_vars_utils(minishell, token, env_vars, i);
	printf("j: %d\n", i);
	env_vars[i] = NULL;
	return (env_vars);
}

char	*return_new_token(t_minishell *minishell, char *token, int size)
{
	char	*new_token;
	char	**env_vars;
	int		env;

	env = count_env_var(token);
	env_vars = malloc ((env + 1) * sizeof(char *));
	if (env_vars == NULL)
		ft_error("Malloc in fill_new_token", minishell);
	env_vars = fill_vars(minishell, env_vars, token, env);
	int	i = 0;
	while(env_vars[i])
		printf("env vars %s\n", env_vars[i++]);
	new_token = fill_new_token(minishell, token, size, env_vars);
	free(env_vars);
	return (new_token);
}