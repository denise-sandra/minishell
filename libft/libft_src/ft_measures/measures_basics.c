/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measures_basics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:51:10 by skanna            #+#    #+#             */
/*   Updated: 2024/07/26 19:10:50 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	int_length(long int n)
{
	int	i;
	int	sign;

	i = 1;
	sign = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = n * -1;
		sign = 1;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (sign + i);
}

int	arg_count(char const *s, char c)
{
	size_t	i;
	size_t	args;

	i = 0;
	args = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			args++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	if (args == 0)
		return (0);
	return (args);
}

int	count_character(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
