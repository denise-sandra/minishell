CC 		= cc
CFLAGS = -Wall -Wextra -Werror -g3 -Iincludes  #-fsanitize=address
LDFLAGS = -lreadline

GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

NAME	:= minishell

SRCS	:= ${addprefix src/, minishell.c \
		${addprefix environement/, split_env_vars.c fill_env_struct.c env_helpers.c copy_list.c} \
		${addprefix lexer/, lexer.c tag_in_quotes.c remove_spaces.c} \
		${addprefix parser/, parser.c parse_redirs.c expand_var.c expand_help.c parse_cmd.c parse_errors.c} \
		${addprefix parser/order_toks/, order_toks.c order_in.c order_out.c} \
		${addprefix exec/, execution.c execute_builtin.c init_fds.c fill_fds.c get_fds.c\
		ft_dup.c dup_tubes.c cmd_exec.c exec_script.c is_slash.c builtin_in_parent.c exec_in_child.c close_fd.c} \
		${addprefix builtins/, env.c exit.c pwd.c cd.c echo.c unset.c} \
		${addprefix builtins/export/, export.c add_var_to_list.c list_to_tab.c} \
		${addprefix utils/, ft_error.c  clean_minishell.c ft_strjoin_free.c token_list.c}}

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

