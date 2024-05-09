/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftv3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:03:17 by skanna            #+#    #+#             */
/*   Updated: 2024/03/15 14:14:00 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTV3_H
# define LIBFTV3_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*clean*/
char	*ft_empty(void);
void	free_tab(char **tab);
char	**free_split(char **split, int h);
void	free_list(t_list **lst);

/*checks*/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		is_nbr(char *str);
int		max_value(int value1, int value2);
int		min_value(int value1, int value2);
int		has_quotes(char const *str);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*measure*/
int		count_digits(char *str);
size_t	ft_strlen(const char *str);
int		int_length(long int n);
int		arg_count(char const *s, char c);
int		arg_len_quotes(char const *str, char c);
int		arg_count_quotes(char const *s, char c, int q);

/*conversions*/
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
int		ft_atoi_err(const char *str, int *error);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	**split_quotes(char const *s, char c);

/*mem alloc and str initialisation*/
void	*ft_memset(void *str, int c, size_t n);
void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t n_items, size_t array_type_size);
char	*ft_strdup(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*str ops*/
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/*search in str*/
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);

/*put_fd*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/*lists*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif