/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/17 15:20:02 by derjavec         ###   ########.fr       */
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
		return (0);
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
		return (0);
     return (quote);
}

int	*check_if_closed_quotes(char *input)
{
	int	single_quotes;
	int	double_quotes;
	int	*quotes;
	
	quotes = NULL;
	double_quotes = check_double_quotes(input);
	if (double_quotes == 0)
		return (NULL);
	single_quotes = check_single_quotes(input);
	if (single_quotes == 0)
		return (NULL);
	quotes[0] = single_quotes;
	quotes[1] = double_quotes;
	return (quotes);
}