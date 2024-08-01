/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/08/01 16:17:34 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	if (isatty(STDIN_FILENO))
	{
		if (rl_line_buffer && rl_line_buffer[0] == '\0')
		{
			rl_replace_line("", 0);
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			rl_replace_line("", 0);
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_redisplay();
		}
	}
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	g_sig = SIGQUIT;
	ft_putstr_fd("Quit\n", 1);
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

void	enable_sigquit(void)
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

void	init_handlers(void)
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

// void	setup_signal_handlers(int ignore)
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = sigint_handler;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	if (sigaction(SIGINT, &sa, NULL) == -1)
// 	{
// 		perror("sigaction for SIGINT");
// 		exit(1);
// 	}
// 	if (ignore)
// 		sa.sa_handler = SIG_IGN;
// 	else
// 		sa.sa_handler = sigquit_handler;
// 	if (sigaction(SIGQUIT, &sa, NULL) == -1)
// 	{
// 		perror("sigaction for SIGQUIT");
// 		exit(1);
// 	}
// }

