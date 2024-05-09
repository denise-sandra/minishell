#include "../Includes/libft_extended.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h> 

int	main(void)
{
	// int fd1 = open ("1-brouette.txt", O_RDONLY);
	// int	fd2 = open ("test.txt", O_RDONLY);
	int	fd = 0;
	char *line;

	// for (int i = 5; i > 0; i--)
	// {
	// 	*line = get_next_line(fd1);
	// 	ft_printf("line fd1: %s\n", line);
	// 	char *line2 = get_next_line(fd2);
	// 	ft_printf("line fd2: %s\n", line2);
	// }
	line = get_next_line(fd);
	while (line)
	{
		printf("line: %s\n", line);
		free (line);
		line = get_next_line(fd);
	}
	// close (fd1);
	// close (fd2);
	close (fd);
	return (0);
}
