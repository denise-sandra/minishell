/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/14 20:34:28 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	*minishell;

	if (argc != 1 || argv[1])
		return (0);
	minishell = init_minishell(envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input && ft_strncmp(input, "exit", ft_strlen(input)) != 0)
		{
			add_history(input);
			tokenize_input(input, minishell);
		}
		else if (*input && ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		{
			free(input);
			break ;
		}
		clean_token(minishell);
		free(input);
	}
	clean_minishell(minishell);
	return (0);
}

//valgrind --suppressions=s.supp ./minishell
