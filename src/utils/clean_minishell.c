/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:24:31 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/29 12:11:41 by derjavec         ###   ########.fr       */
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
	if (minishell->token == NULL)
		return ;
	ft_lstclear_t(&minishell->token, free);
	free (minishell->token);
	minishell->token = NULL;
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
