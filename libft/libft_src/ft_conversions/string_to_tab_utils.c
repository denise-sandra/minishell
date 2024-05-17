/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_tab_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:37:04 by skanna            #+#    #+#             */
/*   Updated: 2024/05/17 09:06:22 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"
#include<stdio.h>
static char	*ft_copyletters_utils(char **tab, int word, int letters, char *s)
{
	int	i;

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

static int	no_quotes(int quotes, int letters, char **ce, char *s)
{
	if (quotes == 0)
	{
		while (s[letters] && s[letters] != ce[0][0])
			letters++;
	}
	return (letters);
}

char	*ft_copyletters(char **tab, int word, char *s, char **ce)
{
	int	letters;
	int	quotes;
	int	i;

	letters = 0;
	quotes = 0;
	i = 0;
	while (ce[1][i])
	{
		if (s[letters] == ce[1][i++])
		{
			quotes = !quotes;
			letters++;
			break ;
		}
	}
	letters = no_quotes(quotes, letters, ce, s);
	if (quotes == 1)
	{
		while (s[letters] && s[letters] != ce[1][i - 1])
		{
			letters++;
		}
		if (s[letters] == ce[1][i - 1])
			letters = letters - 1;
		s = s + 1;
	}
	tab[word] = ft_copyletters_utils(tab, word, letters, s);
	return (tab[word]);
}
