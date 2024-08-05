/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/08/05 17:20:16 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

static char **no_env(t_mini *mini)
{
char **envp;
char cwd[1024];

envp = malloc(4 * sizeof(char *));
if (envp == NULL)
	return (ft_error(mini, NULL, strerror(errno)), NULL);
if (getcwd(cwd, 1024) == NULL)
	return (ft_error(mini, NULL, strerror(errno)), NULL);
envp[0] = ft_strjoin("PWD=", cwd);
if (!envp[0])
	return (free_tab(envp), ft_error(mini, NULL, strerror(errno)), NULL);
envp[1] = ft_strdup("SHLVL=1");
if (!envp[1])
	return (free_tab(envp), ft_error(mini, NULL, strerror(errno)), NULL);
envp[2] = ft_strdup("PATH=/usr/bin/");
if (!envp[2])
	return (free_tab(envp), ft_error(mini, NULL, strerror(errno)), NULL);
envp[3] = NULL;
return (envp);

}

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
	if (envp[0] == NULL)
	envp = no_env(mini);
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
		// enable_sigquit();
		// check_sigs(mini);
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
		return (0);;
	mini = init_minishell(envp);
	minishell(mini);
	final_status = mini->exit_status;
	clean_minishell(mini);
	return (final_status);
}
