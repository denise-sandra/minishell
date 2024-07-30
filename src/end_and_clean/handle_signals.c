/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/07/30 14:40:20 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*sig_mini = NULL;

static void	sigint_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (sig_mini)
		sig_mini->exit_status = 130;
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	if (sig_mini && sig_mini->pid)
	{
		ft_putstr_fd("Quit\n", 1);
		kill(sig_mini->pid[0], SIGQUIT);
		if (sig_mini)
			sig_mini->exit_status = 131;
	}
	else
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_sigquit_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigquit_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGQUIT");
		exit(1);
	}
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
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
