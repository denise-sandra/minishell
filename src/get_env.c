/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/15 20:12:52 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_lst_env *env, char *name)
{
	t_lst_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->name, name, ft_strlen(temp->name)) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

t_lst_env	*env_fill_structure(char **envp, t_minishell *minishell)
{
	char		**split_envp;
	t_lst_env	*lst_env;
	t_lst_env	*new_node;
	int			i;

	lst_env = NULL;
	i = 0;
	while (envp[i])
	{
		split_envp = ft_split_1st_token(envp[i], '=');
		if (split_envp == NULL)
			ft_error("Malloc error in split", minishell);
		new_node = ft_new_node(split_envp[0], split_envp[1]);
		if (new_node == NULL)
			ft_error("Malloc error in new_node", minishell);
		ft_add_back(&lst_env, new_node);
		free_tab(split_envp);
		i++;
	}
	return (lst_env);
}

