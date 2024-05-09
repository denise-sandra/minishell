/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measures_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:37:04 by skanna            #+#    #+#             */
/*   Updated: 2024/03/15 11:11:49 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"

int	arg_len_quotes(char const *str, char c)
{
	int		i;
	int		len;
	int		in_quotes;
	char	q;

	i = 0;
	len = 0;
	in_quotes = 0;
	q = 0;
	while (str[i] && (in_quotes || str[i] != c))
	{
		if ((str[i] == 34 || str[i] == 39) && !in_quotes)
		{
			in_quotes = 1;
			q = str[i];
		}
		else if (str[i] == q && in_quotes)
			in_quotes = 0;
		i++;
		len++;
	}
	return (len);
}

int	arg_count_quotes(char const *s, char c, int q)
{
	size_t	i;
	size_t	args;

	i = 0;
	args = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (q && (s[i] == 34 || s[i] == 39))
		{
			i++;
			args++;
			while (s[i] != 34 && s[i] != 39)
				i++;
			i++;
		}
		else
		{
			args++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (args);
}
