/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ops2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:02:20 by skanna            #+#    #+#             */
/*   Updated: 2024/07/26 19:10:48 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*s1_trimmed;
	size_t		start;
	size_t		end;
	size_t		i;

	i = 0;
	start = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (start == ft_strlen(s1))
		return (ft_empty());
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	s1_trimmed = malloc((end - start + 2) * sizeof(char));
	if (s1_trimmed == NULL)
		return (NULL);
	while (start <= end)
		s1_trimmed[i++] = s1[start++];
	s1_trimmed[i] = '\0';
	return (s1_trimmed);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	str = ft_strdup(s);
	if (!str)
		return (NULL);
	while (str[i])
	{
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}

int	ft_strchr_order(const char *str, int c, int d)
{
	int	count_d;

	count_d = 0;
	while (*str)
	{
		if (*str == (char)d)
			count_d++;
		if (*str == (char)c && count_d % 2 == 0)
			return (1);
		str++;
	}
	if (str[0] == (char)c)
		return (2);
	return (0);
}

int	ft_strrchr_int(char *str, int c)
{
	int	size;

	if (!str)
		return (-1);
	size = ft_strlen(str) - 1;
	if (str[size] == (char)c)
		size--;
	while (size >= 0)
	{
		if (str[size] == (char)c)
			return (size + 1);
		size--;
	}
	return (-1);
}
