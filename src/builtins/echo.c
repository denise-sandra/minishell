/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/06/19 17:36:27 by deniseerjav      ###   ########.fr       */
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
			j = 1;
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

void	echo_command(t_token *cur)
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
