#include "../Includes/libft_extended.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int	main(void)
{
//isalpha
	printf("char: %c, isalpha: %d\n", 65, isalpha(65));
	printf("char: %c, ft_isalpha: %d\n", 65, ft_isalpha(65));
	printf("\n");

//isdigit
	printf("char: %c, isdigit: %d\n", '8', isdigit('8'));
	printf("char: %c,  ft_isdigit: %d\n", '8', ft_isdigit('8'));
	printf("\n");

//isalnum
	printf("char: %c, isalnum: %d\n", 48, isalnum(48));
	printf("char: %c, ft_isalnum: %d\n", 48, ft_isalnum(48));
	printf("\n");

//isascii
	printf("char: %c, isascii: %d\n", '9', isascii(9));
	printf("char: %c, ft_isascii: %d\n", '9', ft_isascii(9));
	printf("\n");

//isprint
	printf("char: %c, ft_isprint: %d, isprint: %d\n", 25, isprint(25), ft_isprint(25));
	printf("\n");

//strncmp
	char	string1[] = "Hello test\200";
	char	string2[] = "Hello 1test1\0";

	printf("string1: %s\nstring2: %s\n", string1, string2);	
	printf("strncmp: %d\n", strncmp(string1, string2, 4));	
	printf("ft_strncmp: %d\n", ft_strncmp(string1, string2, 4));

//memcmp
	printf("memcmp: %d\n", memcmp(string1, string2, 7));	
	printf("ft_memcmp: %d\n", ft_memcmp(string1, string2, 7));
	printf("\n");

return (0);
}
