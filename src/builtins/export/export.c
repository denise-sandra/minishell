/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/08/08 12:22:51 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_nodes(t_lst_env *cur, t_lst_env *next)
{
	char	*name;
	char	*value;

	name = cur->name;
	value = cur->value;
	cur->name = next->name;
	cur->value = next->value;
	next->name = name;
	next->value = value;
}

static void	sort_list(t_lst_env *env)
{
	t_lst_env	*cur;
	t_lst_env	*next;
	int			s;

	s = 1;
	while (s != 0)
	{
		s = 0;
		cur = env;
		while (cur->next)
		{
			next = cur->next;
			if (ft_strncmp(cur->name, next->name, \
				longer_len(cur->name, next->name)) > 0)
			{
				swap_nodes(cur, next);
				s = 1;
			}
			cur = cur->next;
		}
	}
}

static void	print_export(t_lst_env *env)
{
	sort_list(env);
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
		exit(1);
	}
}

void	export_command(t_mini *mini, t_token *cur)
{
	char	*new_var;

	if (mini->export == NULL)
		init_export(mini);
	new_var = cur->cmd_tab[1];
	if (new_var)
		add_var_to_list(mini, cur);
	else
		print_export(mini->export);
	if (mini->error && mini->exit_status == 0)
		mini->exit_status = 1;
}
