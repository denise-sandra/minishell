/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/15 20:22:34 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



//export con una variable (sin valor, solo nombre) se registra y se muestra cuando se llama a export solo
// pero no se muestra cuando se llama a env. Env solo muestra las variables que contienen algun valor

void	export_command(t_minishell *minishell)
{
	int			res;
	char		**split_new_envp;
	t_lst_env	*new_node;
	t_lst_env	*temp;

	new_node = NULL;
	temp = NULL;
	res = 0;
	split_new_envp = NULL;
	if (minishell->token[1])
		res = ft_strchr_int(minishell->token[1]->value, '=');
	else
	{
		temp = minishell->env;
		while (temp)
		{
			printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
			temp = temp->next;
		}
	}
	if (res == 1)
	{
		split_new_envp = ft_split_1st_token(minishell->token[1]->value, '=');
		if (split_new_envp == NULL)
			ft_error("Malloc in export function", minishell);
		new_node = ft_new_node(split_new_envp[0], split_new_envp[1]);
		if (new_node == NULL)
		{
			free_tab(split_new_envp);
			ft_error("Malloc in export function", minishell);
		}
		ft_add_back(&minishell->env, new_node);
	}
	else if (res == 2)
		printf("bash: export: `=': not a valid identifier\n");
	free_tab(split_new_envp);
}
