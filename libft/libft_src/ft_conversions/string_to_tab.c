/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:37:04 by skanna            #+#    #+#             */
/*   Updated: 2024/05/17 09:07:39 by derjavec         ###   ########.fr       */
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

static unsigned int	ft_countwords(char *s, char **ce)
{
	int	i;
	int	words;
	int	quotes;

	if (s[0] == '\0')
		return (0);
	words = 1;
	quotes = 0;
	i = 0;
	while (s[i + 1])
	{
		if (ft_strchr(ce[1], s[i]) != NULL)
			quotes = !quotes;
		if (s[i] == ce[0][0] && !quotes && s[i + 1] != ce[0][0])
			words++;
		i++;
	}
	return (words);
}

static char	**fill_tab(char **tab, int words, char *s, char **ce)
{
	int	i;
	int	len;
	int	q;

	i = 0;
	while (i < words)
	{
		q = 0;
		if (s[0] == ce[1][0] || s[0] == ce[1][1])
			q = 2;
		tab[i] = ft_copyletters(tab, i, s, ce);
		if (tab[i] == NULL)
			return (NULL);
		if (tab[i] == NULL)
			return (NULL);
		len = ft_strlen(tab[i]);
		i++;
		if (i < words)
		{
			s = s + len + q;
			s = s + erase_c(s, ce[0][0]);
		}
	}
	return (tab);
}

char	**ft_split(char *s, char c, char *special_c)
{
	int		words;
	char	**tab;
	char	*ce[2];

	ce[0] = &c;
	ce[1] = special_c;
	if (s == NULL )
		return (NULL);
	s = s + erase_c(s, c);
	words = ft_countwords(s, ce);
	tab = (char **) malloc((words + 1) * sizeof (char *));
	if (tab == NULL)
		return (NULL);
	tab[words] = NULL;
	tab = fill_tab(tab, words, s, ce);
	if (tab == NULL)
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}
