/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/15 22:24:05 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	*minishell;
	int			temp;

	if (argc != 1 || argv[1])
		return (0);
	minishell = init_minishell(envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input && ft_strncmp(input, "exit", 4) != 0)
		{
			add_history(input);
			tokenize_input(input, minishell);
			execution(minishell);
		}
		else if (*input && ft_strncmp(input, "exit", 4) == 0)
		{
			exit_cmd(minishell, input + 4);
			free(input);
			break ;
		}
		clean_token(minishell);
		free(input);
	}
	temp = minishell->last_exit_status;
	clean_minishell(minishell);
	return (temp);
}

//valgrind --suppressions=s.supp ./minishell
