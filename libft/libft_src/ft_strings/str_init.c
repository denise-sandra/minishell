/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:49:28 by skanna            #+#    #+#             */
/*   Updated: 2024/03/15 11:12:44 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)str)[i++] = c;
	return (str);
}

void	ft_bzero(void *str, size_t n)
{
	ft_memset(str, '\0', n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	multip;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	multip = nmemb * size;
	if (multip / nmemb != size)
		return (NULL);
	ptr = malloc(multip);
	if (ptr == NULL)
		return (NULL);
	else
		ft_memset(ptr, 0, multip);
	return (ptr);
}
