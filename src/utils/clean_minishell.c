/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:24:31 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/15 20:12:51 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_env(t_minishell *minishell)
{
	t_lst_env	*current;
	t_lst_env	*next;

	current = minishell->env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	minishell->env = NULL;
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
