CC 		= cc
CFLAGS = -Wall -Wextra -Werror -g3 -Iincludes
LDFLAGS = -lreadline

GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

NAME	:= minishell

SRCS	:= ${addprefix src/, main.c init_minishell.c \
		${addprefix environement/, fill_env_struct.c env_functions.c} \
		${addprefix lexer/, split_input.c check_quotes.c is_command.c} \
		${addprefix parser/, parser.c erase_extra_quotes.c tag_token.c sub_token_in_nodes.c} \
		${addprefix exec/, execution.c execute_builtin.c} \
		${addprefix builtins/, export.c env.c exit.c pwd.c cd.c echo.c} \
		${addprefix utils/, ft_error.c ft_split_1st_token.c pars_path.c clean_minishell.c} \
		${addprefix utils/lists/, create_list_env.c create_list_token.c}}
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

