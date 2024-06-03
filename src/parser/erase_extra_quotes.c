/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_extra_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/03 10:25:09 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static	char	*erase_left_quotes(char *str, int q_type_l, int len)
{
	int		i;
	int		res;
	char	*new_str;
	
	i = len - 1;
	while (i > 0 && str[i] == q_type_l)
		i--;
	res = (len - 1 - i) % 2;
	// printf("len: %d i: %d res: %d\n", len, i, res);
	new_str = malloc((i + 2 + res) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str, i + 2 + res);
	return (new_str);
}

static	char	*erase_right_quotes(char *str, int q_type_r, int len)
{
	int		i;
	int		res;
	char	*new_str;
	
	i = 0;
	while (i < len && str[i] == q_type_r)
		i++;
	res = i % 2;
	new_str = malloc((len - i + res + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str + i - res, len - i + res + 1);
	return (new_str);
}

static char	*copy_new_str(char *str, int q_type_r, int q_type_l, int len)
{
	char	*new_str;
	char	*temp;

	new_str = str;
	// printf("r: %d l: %d\n", q_type_r, q_type_l);
	if (q_type_r != 0)
	{
		temp = erase_right_quotes(new_str, q_type_r, len);
		if (new_str != str)
			free(new_str);
		new_str = temp;
		len = ft_strlen(new_str);
	}
	if (q_type_l != 0)
	{
		new_str = erase_left_quotes(new_str, q_type_l, len);
		if (new_str != str && new_str != temp)
			free(new_str);
		new_str = temp;
	}
	return (new_str);
}

char	*erase_extra_quotes(char *str, int len)
{
	char	*new_str;
	int	q_type_r;
	int	q_type_l;
	
	q_type_r = 0;
	q_type_l = 0;
	new_str = str;
	if (str[0] == 34 || str[0] == 39)
		q_type_r = str[0];
	if (str[len - 1] == 34 || str[len - 1] == 39)
		q_type_l = str[len - 1];
	if (q_type_r != 0 || q_type_l != 0)
		new_str = copy_new_str(str, q_type_r, q_type_l, len);
	if (new_str == NULL)
		return (NULL);
	if (ft_strncmp(str, new_str, len) == 0)
	{
		if (str != new_str)
			free (str);
		return (new_str);
	}	
	return (erase_extra_quotes(new_str, ft_strlen(new_str)));
}