CC 		= cc
CFLAGS = -Wall -Wextra -Werror -g3 -Iincludes
LDFLAGS = -lreadline

GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

NAME	:= minishell

SRCS	:= ${addprefix src/, main.c env.c init_minishell.c lexer.c\
		utils/ft_error.c utils/ft_split_1st_token.c utils/pars_path.c utils/clean_minishell.c}
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

re: clean all

.PHONY: all clean fclean re

