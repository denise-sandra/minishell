/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/24 14:58:27 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(t_lst_env *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		else
			printf("declare -x %s\n", env->name);
		env = env->next;
	}
}

static void	init_export(t_mini *mini)
{
	mini->export = copy_list(mini->env);
	if (!mini->export)
	{
		ft_error(mini, NULL, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	export_command(t_mini *mini, t_token *cur)
{
	char	*new_var;

	init_export(mini);
	new_var = cur->cmd_tab[1];
	if (new_var)
		add_var_to_list(mini, cur);
	else
		print_export(mini->export);
	if (mini->error)
		mini->exit_status = 1;
}
