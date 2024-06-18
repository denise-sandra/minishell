/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/06/18 13:01:45 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_opt(t_token *cur, int *n)
{
	int	i;
	int	res;
	int	j;

	i = 1;
	res = ft_strncmp(cur->cmd_tab[i], "-n", 2);
	while (cur->cmd_tab[i] && res == 0)
	{
		if (ft_strlen(cur->cmd_tab[i]) != 2)
		{
			j = 1;
			while (cur->cmd_tab[i][j])
			{
				if (cur->cmd_tab[i][j++] != 'n')
					res = 1;
			}
		}
		++(*n);
		i++;
		res = ft_strncmp(cur->cmd_tab[i], "-n", 2);
	}
	if (res != 0)
		
	return (i);
}

void	echo_command(t_mini *mini, t_token *cur)
{
	int	i;
	int	j;
	int	n;


	n = -1;
	i = echo_opt(cur, &n);
	printf("5i es %d   cmd: %s\n", i, cur->cmd_tab[i]);
	while (cur->cmd_tab[i])
	{
		j = 0;
		printf("entra\n");
		while (cur->cmd_tab[i][j])
		{
			if (cur->cmd_tab[i][j + 1] && cur->cmd_tab[i][j] == '$' 
				&& cur->cmd_tab[i][j + 1] == '?')
			{
				printf("%d", mini->exit_status);
				j++;
			}
			else
				printf("%c", cur->cmd_tab[i][j]);
			j++;
		}
		if (cur->cmd_tab[i + 1])
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
}
