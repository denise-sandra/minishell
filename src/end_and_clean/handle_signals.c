/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/07/29 18:11:02 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int sig)
{
	// char	*prompt;

	(void) sig;
	printf("\n");
	// prompt = get_dynamic_prompt();
	// printf("%s ^C\n", prompt);
	// free(prompt);
}

// static void	sigquit_handler(int sig)
// {
// 	// char	*prompt;

// 	(void)sig;
// 	printf("\n");
// 	// prompt = get_dynamic_prompt();
// 	// printf("%s ^\\\n", prompt);
// 	// free(prompt);
// }

static void	sigterm_handler(int sig)
{
	(void) sig;
	// sig = SIG_IGN;
	// exit(0);
}

void	setup_signal_handlers(t_mini *mini)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		ft_error(mini, "sigaction for SIGINT", NULL);
		exit(1);
	}
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		ft_error(mini, "sigaction for SIGQUIT", NULL);
		exit(1);
	}
	sa.sa_handler = sigterm_handler;
	if (sigaction(SIGTERM, &sa, NULL) == -1)
	{
		//sigign
		ft_error(mini, "sigaction for SIGTERM", NULL);
		exit(1);
	}
}