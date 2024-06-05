/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/05 00:03:55 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*return_first_env(t_minishell *minishell, char *sub_token)
// {
// 	int		letters;
// 	char	*env_name;
// 	char	*env_value;

// 	letters = env_name_len(sub_token);
// 	env_name = malloc((letters + 1) * sizeof(char));
// 	if (env_name == NULL)
// 		ft_error("malloc in get_env_value");
// 	ft_strlcpy(env_name, sub_token + 1, letters + 1);
// 	env_value = get_env_value(minishell->env, env_name);
// 	if (env_value == NULL)
// 		ft_error("Malloc in ft_strdup");
// 	free(env_name);
// 	if (env_value == NULL)
// 		ft_error("malloc in get_env_value");
// 	return (env_value);
// }

// static char	*expand_env_utils(t_minishell *minishell, char *sub_token)
// {
// 	int		i;
// 	char	*env_value;
// 	char	*res;
// 	char	*tmp;

// 	res = NULL;
// 	env_value = NULL;
// 	tmp = sub_token;
// 	while (tmp[0] != '\0')
// 	{
// 		i = ft_strchr_int(tmp, '$');
// 		if (i == 0)
// 		{
// 			// printf("entra con: %s\n", tmp);
// 			env_value = return_first_env(minishell, tmp);
// 			// printf("env value: %s\n", tmp);
// 			i = env_name_len(tmp) + 1;
// 		}
// 		else
// 		{
// 			res = ft_substr(tmp, 0, i);
// 			if (res == NULL)
// 				ft_error("Malloc in substr");
// 		}
// 		// printf("env %s\n",env_value);
// 		res = ft_strjoin_free(res, env_value);
// 	//printf("res %s\n",res);
// 		if (res == NULL)
// 		{
// 			if (env_value)
// 				free(env_value);
// 			ft_error("3Malloc in parser");
// 		}
// 		tmp = tmp + i;
// 		printf("nuevo env: %s\n", tmp);
// 	}
// 	free(sub_token);
// 	return (res);
// }

// void	expand_env(t_minishell *minishell, t_token **sub_token)
// {
// 	t_token	*tmp;

// 	tmp = *sub_token;
// 	while (tmp)
// 	{
// 		if (tmp->type == ENV)
// 			tmp->value = expand_env_utils(minishell, tmp->value);
// 		tmp = tmp->next;
// 	}
// }
