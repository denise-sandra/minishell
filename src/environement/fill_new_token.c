/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/27 18:50:12 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	replace_name_with_value(char *env_var, char *replaced)
// {
// 	int	i;
// 	int	j;

// 	replaced = malloc(ft_strlen(env_var) * sizeof(char));
// 	if (replaced == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (env_var[i])
// 	{
// 		replaced[j] = env_var[i];
// 		i++;
// 		j++;
// 	}
// 	replaced[j] = '\0';
// }


	// char	*new_token;
	// int		i;
	// int		j;
	// int		k;
	// int		q;

	// new_token = malloc((size + 1) * sizeof(char));
	// if (new_token == NULL)
	// {
	// 	free(env_vars);
	// 	ft_error("Malloc in fill_new_token", minishell);
	// }
	// i = 0;
	// j = 0;
	// k = 0;
	// q = 0;
	// while (j < size)
	// {
	// 	if (token[i] == 39)
	// 		q++;
	// 	if (token[i] == '$' && token[i + 1] && q % 2 == 0)
	// 	{
	// 		j = replace_name_with_value(env_vars[k], new_token, j);
	// 		i = i + env_name_len(token + i) + 1;
	// 		k++;
	// 	}
	// 	else
	// 		new_token[j++] = token[i++];
	// }
	// new_token[j] = '\0';
	// return (new_token);

/*static	int	fill_vars_utils(t_minishell *minishell, t_lst_token **split_token, \
	char **env_vars, int j)
{
	t_lst_token *tmp;
	char	*env_name;
	int		i;

	tmp = *split_token;
	while (tmp)
	{
		i = 0;
		if (tmp->type == ENV)
		{
			while (tmp->value[i])
			{
				if (tmp->value[i] == '$')
				{
					env_name = return_env_str(tmp->value + i);
					if (env_name == NULL)
					{
						free(env_vars);
						ft_error("Malloc in return_env_value", minishell);
					}
					env_vars[j++] = get_env_value(minishell->env, env_name);
					free(env_name);
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
	return (j);
}*/

/*static char	**fill_vars(t_minishell *minishell, char **env_vars, t_lst_token **split_token, int env)
{
	int		i;
	
	i = 0;
	while (i < env)
		i = fill_vars_utils(minishell, split_token, env_vars, i);
	printf("j: %d\n", i);
	env_vars[i] = NULL;
	return (env_vars);
}*/

/*void	return_new_token(t_minishell *minishell, t_lst_token **split_token)
{
	// char	*new_token;
	// char	**env_vars;
	int		env;

	env = count_env_var(split_token);
	// env_vars = malloc ((env + 1) * sizeof(char *));
	// if (env_vars == NULL)
	// 	ft_error("Malloc in fill_new_token", minishell);
	// env_vars = fill_vars(minishell, env_vars, split_token, env);
	// int	i = 0;
	// while(env_vars[i])
	// 	printf("env vars %s\n", env_vars[i++]);
	// fill_new_token(minishell, split_token);
	// free(env_vars);
	// return (new_token);
}*/
