LIBRARY = libft3.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -IIncludes

CHECK_FILES = $(addprefix libft_src/ft_checks/, basic_checks.c cmp_checks.c other_checks.c)
CONV_FILES = $(addprefix libft_src/ft_conversions/, chars_conversion.c ints_and_chars.c string_to_tab.c string_to_tab_utils.c)
LIST_FILES = $(addprefix libft_src/ft_lists/, lst_clean.c lst_content_ops.c lst_node_ops.c lst_search.c)
MEASURE_FILES = $(addprefix libft_src/ft_measures/, measures_basics.c measures_parse.c)
STRING_FILES = $(addprefix libft_src/ft_strings/, mem_ops.c put_fd.c str_clean.c\
			str_init.c str_ops.c str_ops2.c str_search.c )
FT_PRINT_FILES = $(addprefix libft_src/ft_print/, ft_printf.c \
			put_alpha.c put_nbr_hex.c)
GNL_FILES = $(addprefix libft_src/gnl/, get_next_line.c get_next_line_utils.c)

SRC_FILES = $(CHECK_FILES) $(CONV_FILES) $(LIST_FILES) $(MEASURE_FILES) $(STRING_FILES)

OBJ = $(SRC_FILES:.c=.o) $(FT_PRINT_FILES:.c=.o) $(GNL_FILES:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBRARY): $(OBJ)
	@ar -rcs $@ $^
#@echo "Your library has been created"

all: $(LIBRARY)

clean:
	@rm -f $(OBJ)
#@echo "all files deleted successfully!"

fclean: clean
	@rm -f $(LIBRARY)

re: fclean all

.PHONY: all clean fclean re
