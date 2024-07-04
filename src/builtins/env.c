/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/04 14:40:02 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	path_exits(t_lst_env *env)
{
	while (env)
	{
		if (ft_strlen(env->name) == 4 && ft_strncmp(env->name, "PATH", 4) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	env_command(t_mini *mini)
{
	t_lst_env	*temp;

	temp = mini->env;
	if (!path_exits(temp))
	{
		ft_putstr_fd("env: No such file or directory\n", 2);
		error_cleanup(mini);
		mini->error = 1;
		mini->exit_status = 127;
		return ;
	}
	while (temp)
	{
		printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	if (mini->error == 0)
		mini->exit_status = 0;
}
