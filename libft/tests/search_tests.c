#include "../Includes/libft_extended.h"
#include <string.h>
#include <bsd/string.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac == 5)
	{
		char c = av[3][0];
		int n = ft_atoi(av[4]);
	//strchr
		printf("strchr: %s\n", (char*)strchr(av[1], c));
		printf("char address: %p\n", (char*)strchr(av[1], c));
		printf("ft_strchr: %s\n", (char*)ft_strchr(av[1], c));
		printf("char address: %p\n", (char*)ft_strchr(av[1], c));
		printf("\n");

	//strrchr
		printf("strrchr: %s\n", (char*)strrchr(av[1], c));
		printf("char address: %p\n", (char*)strrchr(av[1], c));
		printf("ft_strrchr: %s\n", (char*)ft_strrchr(av[1], c));
		printf("char address: %p\n", (char*)ft_strrchr(av[1], c));
		printf("\n");

	//memchr
		printf("memchr: %s\n", (char*)memchr(av[1], c, n));
		printf("ft_memchr: %s\n", (char*)ft_memchr(av[1], c, n));
		printf("\n");

	//strnstr
		printf("strnstr: %s\n", (char *)strnstr(av[1], av[2], n));
		printf("ft_strnstr: %s\n", (char *)ft_strnstr(av[1], av[2], n));
		printf("\n");
	}
	else
		printf ("Enter parameters: 'long str' 'small str' 'char' 'int'");
return (0);
}
