CC 		= cc
CFLAGS = -Wall -Wextra -Werror -g3 -Iincludes  -fsanitize=address
CPPFLAGS = -I/usr/local/opt/readline/include #para compilar con mac. En linux sacar todos los CPPFLAGS
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline #para compilar con mac. Con linux dejar el otro LDFLAG
#LDFLAGS = -lreadline

GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

NAME	:= minishell

SRCS	:= ${addprefix src/, minishell.c\
		${addprefix environement/, split_env_vars.c fill_env_struct.c env_helpers.c env_aux.c free_env_node.c} \
		${addprefix lexer/, lexer.c tag_in_quotes.c remove_spaces.c} \
		${addprefix parser/, parser.c} \
		${addprefix parser/parse_toks/, parse_hd.c parse_cmd.c parse_errors.c parse_utils.c} \
		${addprefix parser/order_toks/, order_toks.c order_help.c} \
		${addprefix parser/expand/, expand_var.c expand_help.c expand_dq.c} \
		${addprefix parser/tokenize/, token_ops.c tokenize_char.c tokenize_strings.c tokenize_redirs.c} \
		${addprefix exec/, execution.c } \
		${addprefix exec/child/, ft_dup.c dup_tubes.c cmd_exec.c cmd_exec_utils.c access.c exec_in_child.c} \
		${addprefix exec/fd/, init_fds.c fill_fds.c get_fds.c heredoc_help.c close_fd.c} \
		${addprefix exec/exec_builtin/, builtin_in_parent.c execute_builtin.c} \
		${addprefix builtins/, env.c pwd.c echo.c unset.c} \
		${addprefix builtins/export/, export.c add_var_to_list.c list_to_tab.c concat.c} \
		${addprefix builtins/cd/, cd.c go_back.c} \
		${addprefix builtins/exit/, exit.c exit_utils.c} \
		${addprefix end_and_clean/, ft_error.c clean_minishell.c handle_signals.c}}

OBJS     = $(SRCS:.c=.o)

LIBFT := libft/libft3.a
LIBFT_DIR = ./libft

%.o: %.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
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

