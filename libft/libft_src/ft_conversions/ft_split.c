/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:37:04 by skanna            #+#    #+#             */
/*   Updated: 2024/06/10 17:25:14 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"

static unsigned int	erase_spaces(char const *s, char c)
{
	int	start;

	start = 0;
	while (s[start] && s[start] == c)
		start++;
	return (start);
}

static unsigned int	count_words(char const *s, char c)
{
	int	i;
	int	words;

	if (s[0] == '\0')
		return (0);
	i = 0;
	words = 1;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			words++;
		i++;
	}
	return (words);
}

static char	*copy_letters(char **tab, int word, char const *s, char c)
{
	int	i;
	int	letters;

	letters = 0;
	while (s[letters] && s[letters] != c)
		letters++;
	tab[word] = malloc((letters + 1) * sizeof(char));
	if (tab[word] == NULL)
	{
		i = 0;
		while (tab[i])
			free(tab[i++]);
		return (free (tab), NULL);
	}
	i = 0;
	while (s[i] && i < letters)
	{	
		tab[word][i] = s[i];
		i++;
	}
	tab[word][i] = '\0';
	return (tab[word]);
}

static char	**fill_tab(char **tab, int words, char const *s, char c)
{
	int	j;
	int	len;

	j = 0;
	while (words > j)
	{
		tab[j] = copy_letters(tab, j, s, c);
		if (tab[j] == NULL)
			return (NULL);
		len = ft_strlen(tab[j]);
		j++;
		if (j < words)
		{
			s = s + len;
			s = s + erase_spaces(s, c);
		}
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**tab;

	if (s == NULL )
		return (NULL);
	s = s + erase_spaces(s, c);
	words = count_words(s, c);
	tab = (char **) malloc((words + 1) * sizeof (char *));
	if (tab == NULL)
		return (NULL);
	tab[words] = 0;
	tab = fill_tab(tab, words, s, c);
	return (tab);
}
