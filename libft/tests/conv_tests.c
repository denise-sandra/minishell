#include "../Includes/libft_extended.h"
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
/*//toupper
	printf("toupper: %d\n", toupper('c'));
	printf("ft_toupper: %d\n", ft_toupper('c'));
	printf("\n");

//tolower
	printf("tolower: %d\n", tolower('Z'));
	printf("ft_tolower: %d\n", ft_tolower('Z'));
	printf("\n");

//atoi
	char	*string6 = "   +000";
	
	printf("atoi: %d\n", atoi(string6));
	printf("ft_atoi: %d\n", ft_atoi(string6));
	printf("\n");

//itoa
	char	*test_itoa = ft_itoa(0);
	printf("ft_itoa: %s\n", test_itoa);
	free (test_itoa);
	printf("\n");*/

//splits
	char special_c[2];
	special_c[0] = '\'';
	special_c[1] = '\"';
	special_c[2] = '\0';
	char **split = ft_split("'pepe coco lala'", ' ', special_c);
	int	i;
	i = 0;
	while (split[i])
	{
		ft_printf("%s\n", split[i]);
		i++;
	}
return (0);
}
