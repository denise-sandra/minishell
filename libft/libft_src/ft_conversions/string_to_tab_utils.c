/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_tab_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:37:04 by skanna            #+#    #+#             */
/*   Updated: 2024/05/20 14:04:26 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"

static char	*ft_cl_utils(char **tab, int word, int letters, char *s)
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

static int	count_letters(int inside_q, char *s, int quotes)
{
	int	i;
	int	q_type;

	i = 0;
	q_type = s[i];
	if (inside_q == 0)
	{
		while (s[i] && s[i] != 32)
			i++;
	}
	else
	{
		while (s[i] && quotes > 0)
		{
			if (s[i] == q_type)
				quotes--;
			i++;
		}
	}
	return (i);
}

char	*ft_copyletters(char **tab, int word, char *s, int *quotes)
{
	int	letters;
	int	inside_q;
	int	s_d;

	letters = 0;
	inside_q = 0;
	s_d = 2;
	if (s[letters] == 39)
	{
		s_d = 0;
		inside_q = !inside_q;
	}
	if (s[letters] == 34)
	{
		s_d = 1;
		inside_q = !inside_q;
	}
	letters = count_letters(inside_q, s, quotes[s_d]);
	tab[word] = ft_cl_utils(tab, word, letters, s);
	return (tab[word]);
}
