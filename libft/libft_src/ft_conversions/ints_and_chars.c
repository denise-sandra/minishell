/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ints_and_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:51:10 by skanna            #+#    #+#             */
/*   Updated: 2024/04/17 12:32:34 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"

static int	is_sign(long int n)
{
	if (n < 0)
		return (-1);
	else
		return (1);
}

int	count_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			break ;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long int	nbr;
	int			len;
	char		*str;
	int			i;

	nbr = n;
	i = 0;
	len = int_length(nbr);
	str = malloc ((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (nbr < 0)
		str[i++] = 45;
	nbr = nbr * is_sign(nbr);
	str[len] = '\0';
	if (nbr < 10)
		str[i] = nbr + 48;
	while (nbr > 0 && len > 0)
	{
		str[--len] = nbr % 10 + 48;
		nbr = nbr / 10;
	}
	return (str);
}

int	ft_atoi(const char *str)
{
	long	num;
	int		sign;
	int		i;
	int		n;

	num = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45)
		sign = -1;
	if (*str == 43 || *str == 45)
		str++;
	n = count_digits((char *)str);
	i = 0;
	while (i < n)
	{
		num = (num * 10) + (str[i] - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && (-num) < INT_MIN))
			return (0);
		i++;
	}
	return ((int)(num * sign));
}

int	ft_atoi_err(const char *str, int *error)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	if (*str == 45)
		sign = -1;
	if (*str == 43 || *str == 45)
		str++;
	while (*str)
	{
		num = (num * 10) + (*str - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && (-num) < INT_MIN))
		{
			*error = 1;
			return (0);
		}
		str++;
	}
	return ((int)(num * sign));
}
