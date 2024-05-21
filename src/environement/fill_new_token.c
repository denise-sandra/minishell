/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/21 22:02:47 by deniseerjav      ###   ########.fr       */
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
static char    *fill_new_token_utils(t_minishell *minishell, char *token, int size, char **env_vars)
{
	char *new_token;
	int	i;
	int	j;
	int	k;

	new_token = malloc(size * sizeof(char));
    if (new_token == NULL)
        ft_error("Malloc in fill_new_token", minishell);
	i = 0;
	j = 0;
	k = 0;
	while (j < size)
	{
		if (is_env_var(minishell, token, i) == 1)
		{
			j = replace_name_with_value(env_vars[k], new_token, j);
			i = i + env_name_len(token + i);
			k++;
		}
		else
		{
			new_token[j] = token[i];
			j++;
			i++;
		}	
	}
	return (new_token);
}

static char    *fill_env_vars(t_minishell *minishell, char *token)
{
    static int	i = 0;
	char	*env_var;
	
	while (token[i])
	{
		if (is_env_var(minishell, token, i) == 1)
		{
			env_var = return_env_str(minishell, token + i);
			i++;
			return (env_var);
		}
		i++;
	}
    return (NULL);
}

char	*fill_new_token(t_minishell *minishell, char *token, int size)
{
    char    *new_token;
    char    **env_vars;
    int     count_env;
	int		i;
	
    count_env = count_env_var(minishell, token);
    env_vars = malloc ((count_env + 1) * sizeof(char*));
    if (env_vars == NULL)
        ft_error("Malloc in fill_new_token", minishell);  
	i = 0;
	while (i < count_env)
	{ 
		env_vars[i] = fill_env_vars(minishell, token);   
		i++;
	}
	env_vars[i] = NULL;
	new_token = fill_new_token_utils(minishell, token, size, env_vars);
    free(env_vars);
    printf("new token POSTA:%s\n", new_token);
    return (new_token);
}