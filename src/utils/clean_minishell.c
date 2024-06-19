/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:24:31 by derjavec          #+#    #+#             */
/*   Updated: 2024/06/19 14:17:10 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_env(t_mini *minishell)
{
	t_lst_env	*current;
	t_lst_env	*next;

	current = minishell->env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		current->name = NULL;
		current->value = NULL;
		free(current);
		current = next;
	}
	minishell->env = NULL;
}

void	clean_exp(t_mini *minishell)
{
	t_lst_env	*current;
	t_lst_env	*next;

	printf("entra a clean exp\n");
	current = minishell->export;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		current->name = NULL;
		current->value = NULL;
		free(current);
		current = next;
	}
	minishell->export = NULL;
}

void	clean_pretokens(t_mini *minishell)
{
	t_pretok	*temp;

	if (minishell->pretok == NULL)
		return ;
	while (minishell->pretok)
	{
		temp = minishell->pretok->next;
		free(minishell->pretok);
		minishell->pretok = temp;
	}
	minishell->pretok = NULL;
}

// void	clean_token_list(t_mini *minishell)
// {
// 	t_token	*temp;

// 	if (minishell->token == NULL)
// 		return ;
// 	while (minishell->token)
// 	{
// 		temp = minishell->token->next;
// 		if (minishell->token->value)
// 		{
// 			free(minishell->token->value);
// 			minishell->token->value = NULL;
// 		}
// 		if (minishell->token->cmd_tab)
// 		{
// 			free_tab(minishell->token->cmd_tab);
// 			minishell->token->cmd_tab = NULL;
// 		}
// 		free(minishell->token);
// 		minishell->token = temp;
// 	}
// 	minishell->token = NULL;
// }

void	clean_token_list(t_token **list)
{
	t_token	*temp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		if ((*list)->value)
		{
			free((*list)->value);
			(*list)->value = NULL;
		}
		if ((*list)->cmd_tab)
		{
			free_tab((*list)->cmd_tab);
			(*list)->cmd_tab = NULL;
		}
		free(*list);
		*list = temp;
	}
	*list = NULL;
}

void	clean_fd(t_mini *minishell)
{
	if (minishell->fd_in)
	{
		free(minishell->fd_in);
		minishell->fd_in = NULL;
	}
	if (minishell->fd_out)
	{
		free(minishell->fd_out);
		minishell->fd_out = NULL;
	}
	if (minishell->pid)
	{
		free(minishell->pid);
		minishell->pid = NULL;
	}
	if (minishell->tube)
	{
		free(minishell->tube);
		minishell->tube = NULL;
	}
}

void	clean_minishell(t_mini *minishell)
{
	if (minishell->env)
		clean_env(minishell);
	printf("exp: %p\n", minishell->export);
	if (minishell->export)
		clean_exp(minishell);
	if (minishell->env_char)
		free_tab(minishell->env_char);
	if (minishell->pretok)
		clean_pretokens(minishell);
	if (minishell->token)
		clean_token_list(&(minishell->token));
	clean_fd(minishell);
	free(minishell);
}
