#include "../Includes/libft_extended.h"
//#include <bsd/string.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int		n;
	char	c;
	char	*s = NULL;
	int		fd = 2;

	if (ac == 4 && av[2][1] == '\0')
	{
		n = ft_atoi(av[1]);
		c = av[2][0];
		s = av[3];
	
	printf("Initial input: (int) %i, (char) %c, (str) %s\n", n, c, s);
	//putchar	
		printf(" putchar_fd: ");
		ft_putchar_fd(c, fd);
		printf(" putchar: %i\n", ft_putchar(c));
		printf("\n");
	//putstr
		printf(" putstr_fd: ");
		ft_putstr_fd(s, fd);
		printf(" putstr: %i\n", ft_putstr(s));
		printf("\n");
	//putendl_fd
		printf(" putendl_fd: ");
		ft_putendl_fd(s, fd);
		printf("\n");
	//putnbr
		printf(" putnbr_fd: ");
		ft_putnbr_fd (n, fd);
		printf("\n");
	//printf
		ft_printf("print_c: %c\n", c);
		ft_printf("print_s: %s\n", s);
		ft_printf("print_d: %d\n", n);
		ft_printf("print_i: %i\n", n);
		ft_printf("print_u: %u\n", n);
		ft_printf("print_p: %p\n", s);
		ft_printf("print_x: %x, print_X: %X\n", 0, 0);
	}
	else
		printf("Expected params: 'int 'char 'str'\n");
return (0);
}
