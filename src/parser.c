/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/17 08:31:06 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*erase_special_c(char *word, char **ce)
{
	int	i;
	int	q;
	char	*new_word;

	i = 0;
	q = 0;
	while (word[i])
	{
		if (word[i] == ce[1][0] || word[i] == ce[1][1])
			q++;		
		i++;
	}
	new_word = malloc((ft_strlen(word) - q + 1) * sizeof(char));
	if (new_word == NULL)
		return (NULL);
	new_word = //seguir
	free(word);
	return (new_word);
}