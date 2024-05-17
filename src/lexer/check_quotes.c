/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/17 11:35:26 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int   check_double_quotes(char *input)
{
     int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i])
			quote++;
		i++;
	}
	if (quote % 2 != 0)
		return (0);
     return (1);
}

static int   check_single_quotes(char *input)
{
     int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == 39)
			quote++;
		i++;
	}
	if (quote % 2 != 0)
		return (0);
     return (1);
}

int	check_if_closed_quotes(char *input)
{
	if (check_double_quotes(input) == 0)
		return (0);
	if (check_single_quotes(input) == 0)
		return (0);
	
	return (1);
}