/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/06/05 03:24:41 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_minishell	*init_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (minishell == NULL)
	{
		ft_error("Malloc for minishell structure", minishell);
		exit(EXIT_FAILURE);
	}
	ft_bzero(minishell, sizeof(t_minishell));
	minishell->env = fill_env_struct(envp, minishell);
	minishell->builtin[0] = "echo";
	minishell->builtin[1] = "cd";
	minishell->builtin[2] = "pwd";
	minishell->builtin[3] = "export";
	minishell->builtin[4] = "unset";
	minishell->builtin[5] = "env";
	minishell->builtin[6] = "exit";
	return (minishell);
}

static	void	minishell(t_minishell *mini)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input && ft_strncmp(input, mini->builtin[6], 4) != 0)
		{
			add_history(input);
			if (lexer(input, mini) != 0)
			{
				free(input);
				break ;
			}
			clean_pretokens(mini);
			// parser(mini);
			//execution(mini);
		}
		else if (*input && ft_strncmp(input, mini->builtin[6], 4) == 0)
		{
			exit_cmd(mini, input + 4);
			free(input);
			break ;
		}
		// clean_pretokens(mini->pretok);
		clean_token_list(mini->token);
		mini->token = NULL;
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;
	int			temp;

	if (argc != 1 || argv[1])
		return (0);
	mini = init_minishell(envp);
	minishell(mini);
	temp = mini->last_exit_status;
	clean_minishell(mini);
	return (temp);
}

//valgrind --suppressions=s.supp ./minishell 
