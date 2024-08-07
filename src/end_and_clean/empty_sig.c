/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_sig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:35:49 by skanna            #+#    #+#             */
/*   Updated: 2024/08/07 17:00:35 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_empty(int sig)
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

int	handle_sig_int(t_mini *mini)
{
	if (g_sig == SIGINT)
	{
		mini->exit_status = 130;
		g_sig = 0;
		close(mini->here_fd[0]);
		close(mini->here_fd[1]);
		return (-2);
	}
	return (0);
}

void	sigs_here(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction for SIGQUIT");
		exit(1);
	}
}
