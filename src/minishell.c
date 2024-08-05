/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/08/05 18:14:28 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

static void	parse_and_execute(t_mini *mini, char *input)
{
	lexer(input, mini);
	if (!mini->error)
	{
		parser(mini);
		if (!mini->error)
		{
			execution(mini);
			if (mini->error && mini->exit_status == 0)
				mini->exit_status = 1;
		}
	}
}

char	*get_dynamic_prompt(void)
{
	char	cwd[1024];
	char	*prompt;
	char	*temp;

	temp = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		temp = ft_strjoin("minishell:", cwd);
		if (!temp)
			return (ft_strdup("minishell$ "));
		prompt = ft_strjoin(temp, "$ ");
		if (!prompt)
			return (ft_strdup("minishell$ "));
		free (temp);
		return (prompt);
	}
	return (ft_strdup("minishell$ "));
}

static char	*process_input(t_mini *mini, char *prompt, char *input)
{
	input = readline(prompt);
	free (prompt);
	if (!input)
		return (NULL);
	if (*input)
	{
		enable_sigquit();
		check_sigs(mini);
		add_history(input);
		parse_and_execute(mini, input);
	}
	else
	{
		if (g_sig == SIGQUIT)
			g_sig = 0;
	}
	return (input);
}

static void	minishell(t_mini *mini)
{
	char	*prompt;
	char	*input;

	input = NULL;
	while (!mini->should_exit)
	{
		init_handlers();
		g_sig = 0;
		mini->error = 0;
		prompt = get_dynamic_prompt();
		if (!prompt)
			break ;
		input = process_input(mini, prompt, input);
		if (!input)
			break ;
		check_sigs(mini);
		clean_token_list(&(mini->token));
		clean_fd(mini);
		mini->token = NULL;
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	int		final_status;

	if (argc != 1 || argv[1])
		return (0);
	mini = init_minishell(envp);
	minishell(mini);
	final_status = mini->exit_status;
	clean_minishell(mini);
	return (final_status);
}
