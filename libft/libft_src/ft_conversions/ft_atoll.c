/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:38:05 by skanna            #+#    #+#             */
/*   Updated: 2024/06/20 21:34:05 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"

static int	atoll_helper(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

long long	ft_atoll(const char *str, int *err)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = atoll_helper(str, &sign);
	while (ft_isdigit(str[i]))
	{
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
		{
			*err = 1;
			return (0);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		*err = 1;
	return (result * sign);
}
