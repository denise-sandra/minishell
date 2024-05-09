/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/05/09 18:11:35 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "../includes/minishell.h"


void	init_env(char **envp)//funcion dummy para poder testear el makefile
{
	if (!envp)
		return ;
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc != 1 || argv[1])//condiciones dummy para testear el makefile
		return (0);
	//init_prompt(); //-->usar readline en vez de GNL
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input == '\0')
			printf("No input provided\n");
		else
			add_history(input);
		free(input);
		init_env(envp);
	}
	return (0);
}
