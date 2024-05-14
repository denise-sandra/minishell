/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:24:31 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/14 20:29:54 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_env(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->env->vars)
	{
		while (i < minishell->env->count)
		{
			if (minishell->env->vars[i].name)
				free(minishell->env->vars[i].name);
			if (minishell->env->vars[i].value)
				free(minishell->env->vars[i].value);
			i++;
		}
		free(minishell->env->vars);
	}
	free(minishell->env);
}

void	clean_token(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->token == NULL)
		return ;
	while (i < minishell->token_count)
	{
		if (minishell->token[i])
		{
			if (minishell->token[i]->value)
			{
				free(minishell->token[i]->value);
				minishell->token[i]->value = NULL;
			}
			free(minishell->token[i]);
			minishell->token[i] = NULL;
		}
		i++;
	}
	free (minishell->token);
	minishell->token = NULL;
	minishell->token_count = 0;
}


void	clean_minishell(t_minishell *minishell)
{
	if (minishell->env)
		clean_env(minishell);
	if (minishell->token)
		clean_token(minishell);
	if (minishell->output_file)
		free(minishell->output_file);
	if (minishell->input_file)
		free(minishell->input_file);
	free(minishell);
}
