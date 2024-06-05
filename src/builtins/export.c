/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/05 03:30:35 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_command(t_minishell *minishell)
{
	int			res;
	char		**split_new_envp;
	t_lst_env	*new_node;
	t_lst_env	*temp;
	char		*new_var;

	new_node = NULL;
	temp = NULL;
	res = 0;
	split_new_envp = NULL;
	new_var = minishell->token->next->value;
	if (new_var)
		res = ft_strchr_int(new_var, '=');
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
		split_new_envp = split_env_vars(new_var, '=');
		if (split_new_envp == NULL)
			ft_error("Malloc in export function", minishell);
		new_node = ft_lstnew_env(split_new_envp[0], split_new_envp[1]);
		if (new_node == NULL)
		{
			free_tab(split_new_envp);
			ft_error("Malloc in export function", minishell);
		}
		ft_lstadd_back_env(&minishell->env, new_node);
	}
	else if (res == 2)
		printf("bash: export: `=': not a valid identifier\n");
	if (split_new_envp)
		free_tab(split_new_envp);
}
