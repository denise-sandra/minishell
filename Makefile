CC 		= cc
CFLAGS = -Wall -Wextra -Werror -g3 -Iincludes
LDFLAGS = -lreadline

GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

NAME	:= minishell

SRCS	:= ${addprefix src/, main.c init_minishell.c  parser.c \
		${addprefix environement/, env_fill_structure.c get_env.c get_env_utils.c fill_new_token.c} \
		${addprefix lexer/, lexer.c check_quotes.c is_command.c} \
		${addprefix exec/, execution.c execute_special_command.c} \
		${addprefix builtins/, export.c env.c exit.c pwd.c cd.c echo.c} \
		${addprefix utils/, ft_error.c ft_split_1st_token.c pars_path.c clean_minishell.c create_list.c erase_quotes.c}}
OBJS     = $(SRCS:.c=.o)

LIBFT := libft/libft3.a
LIBFT_DIR = ./libft

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "."

all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(LIBFT)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "\n$(GREEN)✔$(RESET) compiled with libft"

clean:
	@rm -rf $(OBJS)
	@echo "object files deleted"

fclean: clean
	@rm -rf $(NAME)
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "all clean! 🧹"

re: fclean all

.PHONY: all clean fclean re

