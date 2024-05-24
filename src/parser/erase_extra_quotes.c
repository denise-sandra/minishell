/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_extra_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/25 00:07:45 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*odd_ext_quotes(char *str, int q_type)
{
	int		i;
	int		j;
	char	*new_str;
	
	i = 0;
	while (str[i] == q_type && str[i + 1] == q_type)
		i++;
	j = ft_strlen(str);
	while (str[j - 1] == q_type &&str[j - 2] == q_type )
		j--;
	new_str = malloc((j - i + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str + i, j - i + 1);
	return (new_str);
}

static	char	*even_ext_quotes(char *str, int q_type)
{
	int		i;
	int		j;
	char	*new_str;
	
	i = 0;
	while (str[i] == q_type)
		i++;
	j = ft_strlen(str);
	while (str[j - 1] == q_type)
		j--;
	new_str = malloc((j - i + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str + i, j - i + 1);
	return (new_str);
}

char	*erase_extra_quotes(char *str)
{
	char	*new_str;          // arreglar, deberia eliminar comillas entre comillas incluso si las de afuera son impares
	int	count;
	int	q_type;
	
	if (str[0] != 34 && str[0] != 39)
		return (str);
	q_type = str[0];
	count = 0;
	while (str[count] == q_type)
		count++;
	if (count < 2)
		return (str);
	if (count % 2 == 0)
		new_str = even_ext_quotes(str, q_type);
	else
		new_str = odd_ext_quotes(str, q_type);
	if (new_str == NULL)
		return (NULL);
	if (new_str != str)
		free (str);
	return (erase_extra_quotes(new_str));
}