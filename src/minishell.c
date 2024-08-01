/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/08/01 15:48:20 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

static t_mini	*init_minishell(char **envp)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (mini == NULL)
	{
		ft_putstr_fd("Failed to malloc minishell structure\n", 2);
		exit(1);
	}
	ft_bzero(mini, sizeof(t_mini));
	mini->env = fill_env_struct(envp, mini);
	if (handle_shlvl(mini) == 1)
		exit(1);
	return (mini);
}

void	parse_and_execute(t_mini *mini, char *input)
{
	lexer(input, mini);
	if (!mini->error)
	{
		parser(mini);
		if (!mini->error)
		{
			execution(mini);
			if (mini->error)
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

static void	minishell(t_mini *mini)
{
	char	*input;
	char	*prompt;

	while (!mini->should_exit)
	{
		init_handlers();
		g_sig = 0;
		mini->error = 0;
		prompt = get_dynamic_prompt();
		if (!prompt)
			break ;
		if (isatty(fileno(stdin)))
			input = readline(prompt);
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			input = ft_strtrim(line, "\n");
			free(line);
		}
		free (prompt);
		if (!input)
			break ;
		enable_sigquit();
		if (*input)
		{
			check_sigs(mini);
			add_history(input);	
			parse_and_execute(mini, input);
		}
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
