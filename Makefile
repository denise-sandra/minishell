CC 		= cc
CFLAGS = -Wall -Wextra -Werror -g3 -Iincludes
LDFLAGS = -lreadline

GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

NAME	:= minishell

SRCS	:= ${addprefix src/, minishell.c \
		${addprefix environement/, split_env_vars.c fill_env_struct.c env_helpers.c } \
		${addprefix lexer/, lexer.c parse_quotes.c remove_spaces.c} \
		${addprefix parser/, parser.c parser_utils.c token_list.c expand_env.c check_syntax_errors.c tag_token.c parse_cmd.c} \
		${addprefix exec/, execution.c execute_builtin.c} \
		${addprefix builtins/, export.c env.c exit.c pwd.c cd.c echo.c} \
		${addprefix utils/, ft_error.c  clean_minishell.c ft_strjoin_free.c}}

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

