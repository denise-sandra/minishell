/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/20 16:34:39 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*erase_all_quotes(char *word)
{
	int	i;
	int	j;
	int	q;
	char	*new_word;

	i = 0;
	q = 0;
	while (word[i])
	{
		if (word[i] == 34 || word[i] == 39)
			q++;		
		i++;
	}
	if (q == 0)
		return (word);
	new_word = malloc((ft_strlen(word) - q + 1) * sizeof(char));
	if (new_word == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (word[j])
	{
		if (word[j] != 34 & word[j] != 39)
		{
			new_word[i] = word[j];
			i++;
		}
		j++;
	}
	free(word);
	return (new_word);
}

char	*erase_outer_quotes(char *word)
{
	int	len;
	int	i;
	char	*new_word;

	if (word[0] != 34 && word[0] != 39)
		return (word);
	len = ft_strlen(word);
	new_word = malloc((ft_strlen(word) - 2 + 1) * sizeof(char));
	if (new_word == NULL)
		return (NULL);
	i = 0;
	while (i + 1 < len - 1)
	{	
		new_word[i] = word[i + 1];
		i++;
	}
	new_word[i] = '\0';
	free(word);
	return (new_word);
}
