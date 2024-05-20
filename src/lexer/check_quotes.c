/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/20 13:37:44 by derjavec         ###   ########.fr       */
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
		if (input[i] == 34)
			quote++;
		i++;
	}
	if (quote % 2 != 0)
		return (-1);
     return (quote);
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
		return (-1);
     return (quote);
}

int	*check_if_closed_quotes(char *input)
{
	int	single_quotes;
	int	double_quotes;
	int	*quotes;
	
	quotes = malloc(3 * sizeof(int));
	if (quotes == NULL)
		return (NULL);
	double_quotes = check_double_quotes(input);
	if (double_quotes == -1)
		return (NULL);
	single_quotes = check_single_quotes(input);
	if (single_quotes == -1)
		return (NULL);
	quotes[0] = single_quotes;
	quotes[1] = double_quotes;
	quotes[2] = -1;
	return (quotes);
}