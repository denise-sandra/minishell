/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/10 16:38:12 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc != 1 || argv[1])//condiciones dummy para testear el makefile
		return (0);
	//init_minishell
	env_fill_structure(envp);
	while (1)
	{
		input = readline("minishell$ ");//displays prompt
		if (!input)
			break ;
		if (*input)
			add_history(input);//updates the working history
		//tokenize_input(input);
		// parse();
		// execute();
		free(input);
	}
	return (0);
}
