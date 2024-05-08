/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:44:25 by derjavec          #+#    #+#             */
/*   Updated: 2023/11/09 08:44:27 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
size_t	ft_strlen0_findline1(const char *c, int choice);
size_t	ft_strlen( const char *c);
t_list	*ft_lstnew_lstaddback(t_list **list, char *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
int		ft_lstlen(t_list *list);
int		lst_find_line(t_list *list);
void	*ft_memcpy(void *d, const void *s, size_t n);

#endif
