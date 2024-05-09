#include "../Includes/libft_extended.h"
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	str1[] = "Hello World";
	char	str2[] = "Hello World";
	
//memset
	printf("Str1: %s, memset: %s\n", str1, (char*)memset(str1, 'a', ft_strlen(str1)));
	printf("Str2: %s, ft_memset: %s\n", str2, (char*)ft_memset(str2, 'a', ft_strlen(str2)));
	printf("\n");
//bzero
	bzero(str1, ft_strlen(str1));
	printf("bzero str1: %s\n", str1);
	ft_bzero(str2, ft_strlen(str2));
	printf("ft_bzero str2: %s\n", str2);	
	printf("\n");

//calloc
	char	*str_mycalloc = "";
	char	*str_calloc = "";
	size_t	n_items = 0;
	size_t	type_size = 0;
	
	str_mycalloc = ft_calloc(n_items, type_size);
	str_calloc = calloc(n_items, type_size);
	
	printf("Calloc test1: %d\n", memcmp(str_mycalloc, str_calloc, n_items));
	printf("Calloc test2: %d\n", ft_memcmp(str_mycalloc, str_calloc, n_items));
	free(str_calloc);
	free(str_mycalloc);
	printf("\n");
return (0);
}
