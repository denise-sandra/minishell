/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/24 14:00:01 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_minishell_utils(t_minishell *minishell, char *input)
{
	add_history(input);
	tokenize_input(input, minishell);
	parser(minishell);
	execution(minishell);
}

static	void	ft_minishell(t_minishell *minishell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input && ft_strncmp(input, "exit", 4) != 0)
		ft_minishell_utils(minishell, input);
		else if (*input && ft_strncmp(input, "exit", 4) == 0)
		{
			exit_cmd(minishell, input + 4);
			free(input);
			break ;
		}
		clean_token(minishell);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;
	int			temp;

	if (argc != 1 || argv[1])
		return (0);
	minishell = init_minishell(envp);
	ft_minishell(minishell);
	temp = minishell->last_exit_status;
	clean_minishell(minishell);
	return (temp);
}

//valgrind --suppressions=s.supp ./minishell
