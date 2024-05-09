#include "../Includes/libft_extended.h"
#include <bsd/string.h>
#include <strings.h>
#include <stdio.h>

static void	test_function(unsigned int index, char *c)
{
	if (c)
		*c = ft_toupper(*c);
	(void)index;
}

static char	test_function2(unsigned int index, char c)
{
	(void)index;
	c = ft_tolower(c);
	return(c);
}

int	main(int ac, char **av)
{
	char	*str1;
	char	*str2;
	int		size;
	int		start;

	if(ac == 6 && are_digits(av[3]) && are_digits(av[4]))
	{
		printf("\n-------STR OPS-------\n\n");
		size = ft_atoi(av[3]);
		if (size > (int)ft_strlen(av[1]))
		{
			printf("Enter a smaller size\n");
			return (-1);
		}
	//strtrim
		printf("Before trim: |%s|\n", av[1]);
		av[1] = ft_strtrim(av[1], av[5]);
		printf("ft_strtrim: |%s|\n", av[1]);
		printf("\n");

	//memcpy & strdup
		str1 = ft_strdup(av[1]);
		printf("String1: |%s|, String2: |%s|\n", av[1], av[2]);
		printf("memcpy: |%s|\n", (char*)memcpy(str1, av[2], size));
		printf("ft_memcpy: |%s|\n", (char*)ft_memcpy(str1, av[2], size));
		printf("\n");
		free (str1);

	//memmove & strdup
		str1 = ft_strdup(av[2]);
		str2 = ft_strdup(av[2]);
		printf("memmove: %s\n", (char*)memmove(str1, av[1], size));
		printf("ft_memmove: %s\n", (char*)ft_memmove(str2, av[1], size));
		free (str1);
		free (str2);
		printf("\n");

	//strlcpy & strdup
		str1 = ft_strdup(av[2]);
		str2 = ft_strdup(av[2]);	
		printf ("dest before: %s\n", str1);
		printf ("strlcpy: %ld, %s\n", strlcpy(str1, av[1], size), str1);
		printf ("ft_strlcpy: %ld, %s\n", ft_strlcpy(str2, av[1], size), str2);
		free (str1);
		free (str2);
		printf("\n");
		
	//strlcat & strdup
		str1 = ft_strdup(av[2]);
		str2 = ft_strdup(av[2]);

		printf ("dest before: %s\n", str1);
		printf ("strlcat: %ld, %s\n", strlcat(str1, av[1], size), str1);
		printf ("ft_strlcat: %ld, %s\n", ft_strlcat(str2, av[1], size), str2);
		free (str1);
		free (str2);
		printf("\n");
	
	//substr & atoi
		start = ft_atoi(av[4]);
		str1 = ft_substr(av[1], start, size);

	//	printf("Original string: %s\n", av[1]);
		printf("starting at index: %i, with len: %i\nft_substr: %s\n", start, size, str1);
		free(str1);
		printf("\n");

	//strjoin
		str1 = ft_strjoin(av[1], av[2]);
		printf("ft_strjoin: %s\n", str1);
		free(str1);
		printf("\n");

	//striteri & strdup
		str1 = ft_strdup(av[1]);
		ft_striteri(str1, test_function);
		printf("striteri: %s\n", str1);
		free(str1);
		printf("\n");

	//strmapi
		str1 = ft_strmapi(av[1], test_function2);
		printf("Strmapi: %s\n", str1);
		free(str1);
	}
	else
		printf("Enter params: 'string1' 'string2' 'int size' 'int start' 'char sep");
    return 0;
}