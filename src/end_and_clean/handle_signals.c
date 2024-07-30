/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/07/30 13:05:38 by skanna           ###   ########.fr       */
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
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signal_handlers(t_mini *mini)
{
	struct sigaction	sa;
	const char			*line;

	sig_mini = mini;
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		ft_error(mini, "sigaction for SIGINT", strerror(errno));
		exit(1);
	}
	line = rl_line_buffer;
	if (line && line[0] == '\0')
	{
		printf("entra a SIG_IGN\n");
		sa.sa_handler = SIG_IGN;
	}
	else
	{
		printf("entra a funcion sigquit\n");
		sa.sa_handler = sigquit_handler;
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		ft_error(mini, "sigaction for SIGQUIT", strerror(errno));
		exit(1);
	}
}
