#include "../Includes/libft_extended.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*str1 = " Hello   this is a.. Test\t .";
	char 	*sq = " this   Is a 'TEST with Quotes' ";
	int		q = has_quotes(sq);

//strlen
	printf("Simple str: %s\n", str1);
	printf("strlen: %zu Vs ft_strlen: %zu\n", strlen(str1), ft_strlen(str1));
//arg_count
	printf("Str with Quote: %s\n", sq);
	printf("Words count: %i\n", arg_count(sq, ' '));
	printf("\n");

//arg_len_quotes
	printf("Arg with quotes: %s\n", sq);
	printf("Arg_len: %i\n", arg_len_quotes(sq, ' '));
//arg_count_quotes
	printf("Words count: %i\n", arg_count_quotes(sq, ' ', q));
	printf("\n");

//int_length
	int nbr = 58963145;
	int neg = -356212158;

	printf("Number: %i, Lenght: %i\n", nbr, int_length(nbr));
	printf("Number: %i, Lenght: %i\n", neg, int_length(neg));
	printf("\n");

return (0);
}
