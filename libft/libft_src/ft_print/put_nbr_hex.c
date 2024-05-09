/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_nbr_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:30:32 by skanna            #+#    #+#             */
/*   Updated: 2024/03/15 11:12:15 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*def_print_base(const char c)
{
	char	*base;

	base = 0;
	if (c == 'd' || c == 'i' || c == 'u')
		base = "0123456789";
	else if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	return (base);
}

static int	ft_print_p2(unsigned long long n)
{
	char	*base;
	int		len;

	base = "0123456789abcdef";
	len = 0;
	if (n >= 16)
		len += ft_print_p2(n / 16);
	len += (ft_putchar(base[n % 16]));
	return (len);
}

int	ft_print_p1(unsigned long long n)
{
	char	*hex;
	int		len;

	len = 0;
	hex = "0x";
	len += ft_putstr(hex);
	len += ft_print_p2(n);
	return (len);
}

int	ft_putsigned(int n, const char c)
{
	long int	nbr;
	char		*base;
	int			len_base;
	int			len;

	nbr = n;
	base = def_print_base(c);
	len_base = ft_strlen(base);
	len = 0;
	if (nbr < 0)
	{
		len += ft_putchar('-');
		nbr = nbr * -1;
	}
	if (nbr >= len_base)
		len += ft_putsigned(nbr / len_base, c);
	len += ft_putchar(base[nbr % len_base]);
	return (len);
}

int	ft_putunsigned(unsigned int n, const char c)
{
	char	*base;
	int		len_base;
	int		len;

	base = def_print_base(c);
	len_base = ft_strlen(base);
	len = 0;
	if (n >= (unsigned int)len_base)
		len += ft_putunsigned(n / (unsigned int)len_base, c);
	len += (ft_putchar(base[n % (unsigned int)len_base]));
	return (len);
}
