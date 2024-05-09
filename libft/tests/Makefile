TESTS = checks conversions gnl measures init print search ops
CC = gcc
Includes = ../Includes
CFLAGS = -Wall -Wextra -Werror -g3 -I$(Includes)

LIBFT = ../libft3.a
LIBFT_DIR = ../

#SRC = $(addprefix blabla/, file1.c file2.c ...)
# OBJ = $(SRC_FILES:.c=.o) $(EXTRA_FILES:.c=.o)
TEST_OBJ = $(wildcard *.o)

%.o: %.c
	@echo "compiling..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "---libft ready to be used---"

default: $(LIBFT)

all:
	@echo "Please run one test at a time. Available tests: $(TESTS)"

checks: check_tests.o $(LIBFT)
	@$(CC) $(CFLAGS) $< -o $@ $(LIBFT)
	@./$@

conversions: conv_tests.o $(LIBFT)
	@$(CC) $(CFLAGS) $< -o $@ $(LIBFT)
	@./$@

gnl: gnl_test.o $(LIBFT)
	@$(CC) $(CFLAGS) $< -o $@ $(LIBFT)
	@./$@

measures: measures_tests.o $(LIBFT)
	@$(CC) $(CFLAGS) $< -o $@ $(LIBFT)
	@./$@
	
init: malloc_init_tests.o $(LIBFT)
	@$(CC) $(CFLAGS) $< -o $@ $(LIBFT)
	@./$@
	
print: print_tests.o $(LIBFT)
	@$(CC) $(CFLAGS) $< -o $@ $(LIBFT)
	@./$@
	
search: search_tests.o $(LIBFT)
	@$(CC) $(CFLAGS) $< -o $@ $(LIBFT) -lbsd
	@./$@
	
ops: str_ops_tests.o $(LIBFT)
	@$(CC) $(CFLAGS) $< -o $@ $(LIBFT) -lbsd
	@./$@
	
clean:
	@rm -f $(TEST_OBJ)
	@echo "all files deleted successfully!"

fclean: clean
	@rm -f $(TESTS)
	@make --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re checks conversions gnl\
		measures init print search ops