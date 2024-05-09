#include "../Includes/libft_extended.h"
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
//toupper
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
	printf("\n");

//splits
	char *s1 = "grep	And";
	char *s2 = "sed    's/And/But/'";
	char **split;
	char **split_q;

	printf("Single string to be copied: |%s|\n", s1);
	split = ft_split(s1, ' ');
	for (int i = 0; split[i]; i++)
	{
		printf("String %d: |%s|\n", i, split[i]);
		free (split[i]);
		printf("\n");
	}
	free (split);
	printf("Complex string to be copied: |%s|\n", s2);
	split_q = split_quotes((char const *)s2, ' ');
	for (int i = 0; split_q[i]; i++)
	{
		printf("String %d: |%s|\n", i, split_q[i]);
		free (split_q[i]);
	}
	free (split_q);
	printf("\n");

return (0);
}
