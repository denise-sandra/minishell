/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/06/18 14:41:18 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_opt(t_token *cur, int *n)
{
	int	i;
	int	j;

	i = 1;
	while (cur->cmd_tab[i] && ft_strncmp(cur->cmd_tab[i], "-n", 2) == 0)
	{
		if (ft_strlen(cur->cmd_tab[i]) > 2)
		{
			j = 0;
			while (cur->cmd_tab[i][j])
			{
				if (cur->cmd_tab[i][j] != 'n')
					break ;
				j++;
			}
			if (cur->cmd_tab[i][j] == '\0')
				++(*n);
		}
		else
			++(*n);
		if (ft_strlen(cur->cmd_tab[i]) == 2 || *n > 0)
			i++;
		else
			break ;
	}
	return (i);
}

void	echo_command(t_mini *mini, t_token *cur)
{
	int	i;
	int	j;
	int	n;


	n = 0;
	i = echo_opt(cur, &n);
	while (cur->cmd_tab[i])
	{
		j = 0;
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
