/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fill_structure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/21 15:26:25 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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