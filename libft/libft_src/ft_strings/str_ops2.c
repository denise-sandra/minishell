/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ops2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:02:20 by skanna            #+#    #+#             */
/*   Updated: 2024/05/21 13:18:35 by deniseerjav      ###   ########.fr       */
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


