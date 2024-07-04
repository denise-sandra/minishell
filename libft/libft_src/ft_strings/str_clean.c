/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:02:20 by skanna            #+#    #+#             */
/*   Updated: 2024/07/04 14:06:50 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"

char	*ft_empty(void)
{
	char	*str;

	str = malloc(1);
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	**ft_empty_tab(void)
{
	char	**tab;

	tab = malloc(sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab[0] = NULL;
	return (tab);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free (tab[i]);
		i++;
	}
	free(tab);
}

char	**free_split(char **split, int h)
{
	int	i;

	i = 0;
	while (i < h)
	{
		free (split[i]);
		i++;
	}
	free(split);
	return (NULL);
}
