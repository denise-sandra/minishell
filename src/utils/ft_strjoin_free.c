/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/06/19 09:37:21 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joint;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joint = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (joint == NULL)
		return (NULL);
	while (s1[j])
		joint [i++] = (s1)[j++];
	j = 0;
	while (s2[j])
		joint[i++] = (s2)[j++];
	free(s1);
	free(s2);
	joint[i] = '\0';
	return (joint);
}

char	*ft_strjoin_char(char *s, char c)
{
	char	*joint;
	size_t	len_s;

	if (s == NULL)
		len_s = 0;
	else
		len_s = ft_strlen(s);
	joint = malloc((len_s + 2) * sizeof(char));
	if (joint == NULL)
		return (NULL);
	if (s)
		ft_memcpy(joint, s, len_s);
	joint[len_s] = c;
	joint[len_s + 1] = '\0';
	free(s);
	return (joint);
}

char	*ft_strjoin_frees1(char *s1, char *s2)
{
	char	*joint;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joint = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (joint == NULL)
		return (NULL);
	while (s1[j])
		joint [i++] = (s1)[j++];
	j = 0;
	while (s2[j])
		joint[i++] = (s2)[j++];
	free(s1);
	joint[i] = '\0';
	return (joint);
}