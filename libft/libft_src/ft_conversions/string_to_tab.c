/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:37:04 by skanna            #+#    #+#             */
/*   Updated: 2024/05/20 13:35:45 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"

static unsigned int	erase_c(char *s, char c)
{
	int	start;

	start = 0;
	while (s[start] && s[start] == c)
		start++;
	return (start);
}

static unsigned int	ft_countwords(char *s, int *quotes)
{
	int	i;
	int	words;
	int	q;
	int	inside_q;

	if (s[0] == '\0')
		return (0);
	words = 1;
	q = 0;
	i = 0;
	inside_q = 0;
	while (s[i + 1])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			q++;
			if (s[i] == 39 && (q == 1 || q == quotes[0]))
				inside_q = !inside_q;
			if (s[i] == 34 && (q == 1 || q == quotes[1]))
				inside_q = !inside_q;
		}
		if (s[i] == 32 && inside_q == 0 && s[i + 1] != 32)
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
		{
			free(quotes);
			return (NULL);
		}	
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

	if (s == NULL )
		return (NULL);
	s = s + erase_c(s, c);
	words = ft_countwords(s, quotes);
	tab = (char **) malloc((words + 1) * sizeof (char *));
	if (tab == NULL)
	{
		free(quotes);
		return (NULL);
	}
	tab[words] = NULL;
	tab = fill_tab(tab, words, s, quotes);
	if (tab == NULL)
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}
