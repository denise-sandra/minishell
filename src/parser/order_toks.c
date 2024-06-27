/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_toks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:28:18 by sandra            #+#    #+#             */
/*   Updated: 2024/06/27 15:04:07 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	order_in(t_mini *mini)
{
	t_token *cur = mini->token;
	t_token *prev = NULL;
	t_token *redir_head = NULL;
	t_token *redir_tail = NULL;
	t_token *cmd_head = NULL;
	t_token *cmd_tail = NULL;

	while (cur)
	{
		t_token *next = cur->next;

		if (cur->type == PIPE)
		{
			// Combine redirection tokens and command tokens for the current segment
			if (redir_tail)
			{
				redir_tail->next = cmd_head;
				cmd_tail->next = NULL; // End of command segment
				if (prev)
					prev->next = redir_head;
				else
					mini->token = redir_head;
				prev = cmd_tail ? cmd_tail : redir_tail;
			}
			else if (cmd_tail)
			{
				if (prev)
					prev->next = cmd_head;
				else
					mini->token = cmd_head;
				prev = cmd_tail;
			}

			// Set the pipe token
			if (prev)
				prev->next = cur;
			prev = cur;

			// Reset the lists for the next segment
			redir_head = redir_tail = NULL;
			cmd_head = cmd_tail = NULL;

			cur = next;
			continue;
		}
		else if (cur->type == IN || cur->type == HERE)
		{
			// Handle input redirection token
			if (redir_tail)
			{
				redir_tail->next = cur;
				redir_tail = cur;
			}
			else
			{
				redir_head = cur;
				redir_tail = cur;
			}

			// Check if the next token is a string (filename or heredoc delimiter)
			if (next && next->type == STRING)
			{
				redir_tail->next = next;
				redir_tail = next;
				cur = next->next;
			}
			else
			{
				cur = next;
			}
		}
		else
		{
			// Handle command/option/string token
			if (cmd_tail)
			{
				cmd_tail->next = cur;
				cmd_tail = cur;
			}
			else
			{
				cmd_head = cur;
				cmd_tail = cur;
			}
			cur->next = NULL;
			cur = next;
		}
	}

	// Combine the last segment's redirection tokens and command tokens
	if (redir_tail)
	{
		redir_tail->next = cmd_head;
		if (cmd_tail)
			cmd_tail->next = NULL;
		if (prev)
			prev->next = redir_head;
		else
			mini->token = redir_head;
	}
	else if (cmd_tail)
	{
		if (prev)
			prev->next = cmd_head;
		else
			mini->token = cmd_head;
	}
}
