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

static char	*ft_copylettres_reduc(char **tableau, int mot, int lettres, char *s)
{
	int	i;

	tableau[mot] = malloc((lettres + 1) * sizeof(char));
	if (tableau[mot] == NULL)
	{
		i = 0;
		while (tableau[i])
			free(tableau[i++]);
		return (free (tableau), NULL);
	}
	i = 0;
	while (s[i] && i < lettres)
	{	
		tableau[mot][i] = s[i];
		i++;
	}
	tableau[mot][i] = '\0';
	return (tableau[mot]);
}

static int	no_quotes(int quotes, int lettres, char **ce, char *s)
{
	if (quotes == 0)
	{
		while (s[lettres] && s[lettres] != ce[0][0])
			lettres++;
	}
	return (lettres);
}

char	*ft_copylettres(char **tableau, int mot, char *s, char **ce)
{
	int	lettres;
	int	quotes;
	int	i;

	lettres = 0;
	quotes = 0;
	i = 0;
	while (ce[1][i])
	{
		if (s[lettres] == ce[1][i++])
		{
			quotes = !quotes;
			lettres++;
		}
	}
	lettres = no_quotes(quotes, lettres, ce, s);
	if (quotes == 1)
	{
		while (s[lettres] && s[lettres] != ce[1][i])
			lettres++;
		lettres = lettres - 2;
		s = s + 1;
	}
	tableau[mot] = ft_copylettres_reduc(tableau, mot, lettres, s);
	return (tableau[mot]);
}