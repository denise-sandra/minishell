/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/08/07 11:49:48 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	sigquit_in_line(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit\n", 1);
	g_sig = SIGQUIT;
}



void	check_sigs(t_mini *mini)
{
	if (g_sig == SIGINT)
	{
		mini->exit_status = 130;
		g_sig = 0;
	}
	else if (g_sig == SIGQUIT)
	{
		mini->exit_status = 131;
		g_sig = 0;
	}
}

void	sigint_in_line(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_redisplay();
}

void	sigs_in_line(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_in_line;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGINT");
		exit(1);
	}
	sa.sa_handler = sigquit_in_line;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGQUIT");
		exit(1);
	}
}

void	sigint_empty(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

void	sigs_empty(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_empty;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGINT");
		exit(1);
	}
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGQUIT");
		exit(1);
	}
}
