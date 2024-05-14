/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_1st_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:16:03 by derjavec          #+#    #+#             */
/*   Updated: 2024/05/14 19:12:15 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_letters_until_end(char **tab, char const *s)
{
	int	i;
	int	letters;

	letters = 0;
	while (s[letters])
		letters++;
	tab[1] = malloc((letters + 1) * sizeof(char));
	if (!tab[1])
		return (NULL);
	i = 0;
	while (s[i] && i < letters)
	{	
		tab[1][i] = s[i];
		i++;
	}
	tab[1][i] = '\0';
	return (tab[1]);
}


static char	*copy_letters_until_c(char **tab, char const *s, char c)
{
	int	i;
	int	letters;

	letters = 0;
	while (s[letters] && s[letters] != c)
		letters++;
	tab[0] = malloc((letters + 1) * sizeof(char));
	if (!tab[0])
		return (NULL);
	i = 0;
	while (s[i] && i < letters)
	{	
		tab[0][i] = s[i];
		i++;
	}
	tab[0][i] = '\0';
	return (tab[0]);
}

static char	**fill_tab(char **tab, char const *s, char c)
{
	int	len;

	tab = malloc(3 * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab[0] = copy_letters_until_c(tab, s, c);
	if (!tab[0])
		return (free(tab), NULL);
	len = ft_strlen(tab[0]);
	s = s + len;
	tab[1] = copy_letters_until_end(tab, s);
	if (!tab[1])
		return (free_tab(tab), NULL);
	tab[2] = NULL;
	return (tab);
}

char	**ft_split_1st_token(char const *s, char c)
{
	char	**tab;

	if (s == NULL )
		return (NULL);
	tab = NULL;
	tab = fill_tab(tab, s, c);
	return (tab);
}
