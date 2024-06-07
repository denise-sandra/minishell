/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/06/07 13:52:39 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_minishell	*init_minishell(char **envp)
{
	t_minishell	*mini;

	mini = malloc(sizeof(t_minishell));
	if (mini == NULL)
	{
		ft_error("Malloc for minishell structure", mini);
		exit(EXIT_FAILURE);
	}
	ft_bzero(mini, sizeof(t_minishell));
	mini->env = fill_env_struct(envp, mini);
	mini->builtin[0] = "echo";
	mini->builtin[1] = "cd";
	mini->builtin[2] = "pwd";
	mini->builtin[3] = "export";
	mini->builtin[4] = "unset";
	mini->builtin[5] = "env";
	mini->builtin[6] = "exit";
	return (mini);
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
			if (lexer(input, mini) == 0)
			{
				parser(mini);
				t_token *tmp = mini->token;
				while (tmp)
				{
					printf("%s\n", tmp->value);
					tmp = tmp->next;
				}
				//execution(mini);
			}	
		}
		else if (*input && ft_strncmp(input, mini->builtin[6], 4) == 0)
		{
			exit_cmd(mini, input + 4);
			free(input);
			break ;
		}
		clean_token_list(mini->token);
		mini->token = NULL;
		free(input);
	}
}

// trate con esto y hace segfault. deberia decir que las comillas no estan cerradas: ""`" cat" << pepeloco
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
