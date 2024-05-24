/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/24 12:23:39 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_double_quotes(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == 34)
			quote++;
		i++;
	}
	return (quote);
}

static int	check_single_quotes(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == 39)
			quote++;
		i++;
	}
	return (quote);
}

int	*check_quotes(char *str)
{
	int	single_quotes;
	int	double_quotes;
	int	*quotes;

	quotes = malloc(3 * sizeof(int));
	if (quotes == NULL)
		return (NULL);
	double_quotes = check_double_quotes(str);
	single_quotes = check_single_quotes(str);
	quotes[0] = single_quotes;
	quotes[1] = double_quotes;
	quotes[2] = -1;
	return (quotes);
}
