/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:44:48 by derjavec          #+#    #+#             */
/*   Updated: 2023/11/09 08:44:50 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static t_list	*fill_list(char *content, t_list *list)
{
	int			letters;
	static char	*node;
	int			i;

	while (content != NULL && content[0] != '\0')
	{
		letters = ft_strlen0_findline1(content, 1);
		node = malloc ((letters + 1) * sizeof(char));
		if (node == NULL)
			return (ft_lstclear(&list, free), NULL);
		i = 0;
		while (i < letters && content[i])
		{
			node[i] = content[i];
			i++;
		}
		node[i] = '\0';
		list = ft_lstnew_lstaddback(&list, node);
		if (list == NULL)
			return (free(node), NULL);
		content = content + letters;
	}
	return (list);
}

static void	copy_list_to_line(char *content, t_list **list, int content_size)
{
	int		i;
	int		j;
	t_list	*temp;

	if (list == NULL || *list == NULL)
		return ;
	i = 0;
	j = 0;
	temp = *list;
	while (temp && i < content_size)
	{
		content[i] = temp->content[j];
		if (temp->content[j + 1] == '\0')
		{
			temp = temp->next;
			j = 0;
		}
		else
			j++;
		i++;
	}
	content[i] = '\0';
	return ;
}

static t_list	*clean_completed_lines(t_list **list)
{
	t_list	*temp;

	temp = *list;
	while (temp && ft_strlen0_findline1(temp->content, 2) == 0)
	{
		free(temp->content);
		*list = temp->next;
		free(temp);
		temp = *list;
	}
	if (temp && temp->next)
	{
		*list = temp->next;
		free(temp->content);
		free(temp);
	}
	else if (temp)
	{
		free(temp->content);
		free(temp);
		*list = NULL;
	}
	else
		*list = NULL;
	return (*list);
}

static char	*list_to_line(t_list **list, char *line, int content_size)
{
	line = malloc((content_size + 1) * sizeof(char));
	if (line == NULL)
		return (ft_lstclear(list, free), NULL);
	copy_list_to_line(line, list, content_size);
	*list = clean_completed_lines(list);
	return (line);
}

char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE + 1];
	static t_list	*list = NULL;
	char			*line;
	int				r;

	r = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (lst_find_line(list) != 1 && r > 0)
	{	
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
			return (ft_lstclear(&list, free), NULL);
		buf[r] = '\0';
		list = fill_list(buf, list);
		if (list == NULL)
			return (ft_lstclear(&list, free), NULL);
	}
	line = NULL;
	if (ft_lstlen(list) > 0)
		line = list_to_line(&list, line, ft_lstlen(list));
	return (line);
}
