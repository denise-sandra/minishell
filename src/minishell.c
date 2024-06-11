/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/06/11 15:42:42 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mini	*init_minishell(char **envp)
{
	t_mini	*minishell;

	minishell = malloc(sizeof(t_mini));
	if (minishell == NULL)
	{
		ft_error("Malloc for minishell structure", minishell);
		exit(EXIT_FAILURE);
	}
	ft_bzero(minishell, sizeof(t_mini));
	minishell->env = fill_env_struct(envp, minishell);
	return (minishell);
}

static	void	minishell(t_mini *mini)
{
	char	*input;

	while (1)
	{
		mini->error = 0;
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input && ft_strncmp(input, "exit", 4) != 0)
		{
			add_history(input);
			lexer(input, mini);
			parser(mini);
			// t_token *tmp;
			// while (tmp)
			// {
				
			// }
			//execution(mini);
		}
		else if (*input && ft_strncmp(input, "exit", 4) == 0)
		{
			exit_cmd(mini, input + 4);
			free(input);
			break ;
		}
		clean_token_list(&(mini->token)); //temporal para no tener leaks: esto va en execution()
		mini->token = NULL;
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	int		temp;

	if (argc != 1 || argv[1])
		return (0);
	mini = init_minishell(envp);
	minishell(mini);
	temp = mini->exit_status;
	clean_minishell(mini);
	return (temp);
}

//valgrind --suppressions=s.supp ./minishell 
