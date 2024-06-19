/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/06/19 12:28:35 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static t_mini	*init_minishell(char **envp)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (mini == NULL)
	{
		ft_error("Malloc for minishell structure", mini);
		exit(EXIT_FAILURE);
	}
	ft_bzero(mini, sizeof(t_mini));
	mini->env = fill_env_struct(envp, mini);
	mini->export = copy_list(mini->env);
	if (!mini->export)
	{
		ft_error("Malloc for minishell structure", mini);
		exit(EXIT_FAILURE);
	}
	return (mini);
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
			if (!mini->error)
			{
				execution(mini);
				if (!mini->error)
					mini->exit_status = 1;
			}
		}
		else if (*input && ft_strncmp(input, "exit", 4) == 0)
		{
			exit_cmd(mini, input + 4);
			free(input);
			break ;
		}
		clean_token_list(&(mini->token));
		clean_fd(mini);
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

//valgrind --suppressions=s.supp --track-origins=yes --show-leak-kinds=all --track-fds=yes ./minishell 
