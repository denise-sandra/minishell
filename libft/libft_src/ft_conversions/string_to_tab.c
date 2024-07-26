/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:37:04 by skanna            #+#    #+#             */
/*   Updated: 2024/07/26 19:08:04 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"
#include <stdio.h>

static unsigned int	erase_c(char *s, char c)
{
	int	start;

	start = 0;
	while (s[start] && s[start] == c)
		start++;
	return (start);
}

static unsigned int	ft_countwords(char *s)
{
	int	i;
	int	words;
	int	s_q;
	int	d_q;

	words = 1;
	s_q = 0;
	d_q = 0;
	i = 0;
	while (s[i + 1])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			if (s[i] == 39)
				s_q++;
			if (s[i] == 34)
				d_q++;
		}
		if (s[i] == 32 && s_q % 2 == 0 && d_q % 2 == 0 && s[i + 1] != 32)
			words++;
		i++;
	}
	return (words);
}

static char	**fill_tab(char **tab, int words, char *s, int *quotes)
{
	int	i;
	int	len;

	i = 0;
	while (i < words)
	{
		tab[i] = ft_copyletters(tab, i, s, quotes);
		if (tab[i] == NULL)
			return (NULL);
		len = ft_strlen(tab[i]);
		i++;
		if (i < words)
		{
			s = s + len;
			s = s + erase_c(s, 32);
		}
	}
	return (tab);
}

char	**ft_split_quotes(char *s, char c, int *quotes)
{
	int		words;
	char	**tab;

	s = s + erase_c(s, c);
	if (s[0] == 0)
	{
		tab = ft_empty_tab();
		if (tab == NULL)
			return (NULL);
		return (tab);
	}
	words = ft_countwords(s);
	printf("words: %d\n", words);
	tab = malloc((words + 1) * sizeof (char *));
	if (tab == NULL)
		return (NULL);
	tab[words] = NULL;
	tab = fill_tab(tab, words, s, quotes);
	if (tab == NULL)
		return (free(tab), NULL);
	return (tab);
}
