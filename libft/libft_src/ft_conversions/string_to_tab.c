/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:37:04 by skanna            #+#    #+#             */
/*   Updated: 2024/03/15 11:13:44 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"

static unsigned int	ft_effc(char *s, char c)
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
	int	mots;
	int	quotes;

	if (s[0] == '\0')
		return (0);
	mots = 1;
	quotes = 0;
	i = 0;
	while (s[i + 1])
	{
		if (ft_strchr(ce[1], s[i]) != NULL)
			quotes = -1;
		if (s[i] == ce[0][0] && !quotes && s[i + 1] != ce[0][0])
			mots++;
		i++;
	}
	return (mots);
}

static char	**reduc(char **tableau, int mots, char *s, char **ce)
{
	int	j;
	int	lenmot;

	j = 0;
	while (mots > j)
	{
		tableau[j] = ft_copylettres(tableau, j, s, ce);
		if (tableau[j] == NULL)
			return (NULL);
		lenmot = ft_strlen(tableau[j]);
		j++;
		if (j < mots)
		{
			s = s + lenmot;
			s = s + ft_effc(s, ce[0][0]);
		}
	}
	return (tableau);
}

char	**ft_split(char *s, char c, char *special_c)
{
	int		mots;
	char	**tableau;
	char	*ce[2];

	ce[0] = &c;
	ce[1] = special_c;
	if (s == NULL )
		return (NULL);
	s = s + ft_effc(s, c);
	mots = ft_countwords(s, ce);
	tableau = (char **) malloc((mots + 1) * sizeof (char *));
	if (tableau == NULL)
		return (NULL);
	tableau[mots] = NULL;
	tableau = reduc(tableau, mots, s, ce);
	if (tableau == NULL)
	{
		free(tableau);
		return (NULL);
	}
	return (tableau);
}