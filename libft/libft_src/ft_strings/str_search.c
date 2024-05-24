/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:02:03 by skanna            #+#    #+#             */
/*   Updated: 2024/05/24 09:58:03 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] != (unsigned char)c)
			i++;
		else
			return ((unsigned char *)(s + i));
	}
	return (NULL);
}

int	ft_strchr_int(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return (1);
		str++;
	}
	if (str[0] == (char)c)
		return (2);
	return (0);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

char	*ft_strrchr(const char *str, int c)
{
	int	size;

	size = ft_strlen(str);
	while (size >= 0)
	{
		if (*(char *)(str + size) == (char)c)
			return ((char *)(str + size));
		size--;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((j + i) < len && (little[i]) && (big[j]))
	{
		if (little[i] == big[j + i])
			i++;
		else
		{
			i = 0;
			j++;
		}
	}
	if (little[i] == '\0')
		return ((char *)big + j);
	else
		return (NULL);
}
