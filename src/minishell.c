/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/07/25 17:27:04 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mini	*init_minishell(char **envp)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (mini == NULL)
	{
		ft_putstr_fd("Failed to malloc minishell structure\n", 2);
		exit(1);
	}
	ft_bzero(mini, sizeof(t_mini));
	mini->env = fill_env_struct(envp, mini);
	mini->env_char = list_to_tab(mini);
	if (mini->error == 1)
		exit(1);
	return (mini);
}

void	parse_and_execute(t_mini *mini, char *input)
{
	lexer(input, mini);
	if (!mini->error)
	{
		parser(mini);
		if (!mini->error)
		{
			execution(mini);
			if (mini->error)
				mini->exit_status = 1;
		}
	}
}

char	*get_dynamic_prompt(void)
{
	char	cwd[1024];
	char	*prompt;
	char	*temp;

	temp = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		temp = ft_strjoin("minishell:", cwd);
		if (!temp)
			return (ft_strdup("minishell$ "));
		prompt = ft_strjoin(temp, "$ ");
		if (!prompt)
			return (ft_strdup("minishell$ "));
		free (temp);
		return (prompt);
	}
	return (ft_strdup("minishell$ "));
}

static void	minishell(t_mini *mini)
{
	char	*input;
	char	*prompt;

	setup_signal_handlers(mini);
	while (!mini->should_exit)
	{
		mini->error = 0;
		prompt = get_dynamic_prompt();
		if (!prompt)
			break ;
		if (isatty(fileno(stdin)))
			input = readline(prompt);
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			input = ft_strtrim(line, "\n");
			free(line);
		}
		free (prompt);
		if (!input)
			break ;
		if (*input)
		{
			add_history(input);
			parse_and_execute(mini, input);
		}
		clean_token_list(&(mini->token));
		clean_fd(mini);
		mini->token = NULL;
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	int		final_status;

	if (argc != 1 || argv[1])
		return (0);
	mini = init_minishell(envp);
	minishell(mini);
	final_status = mini->exit_status;
	clean_minishell(mini);
	return (final_status);
}



/*

leaks al usar las senales dentro de un heredoc abierto:

skanna@k2r3p1:Documents/minishell ‹exec*›$ valgrind --suppressions=s.supp --track-origins=yes --show-leak-kinds=all --track-fds=yes --leak-check=full  ./minishell
==1352720== Memcheck, a memory error detector
==1352720== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1352720== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==1352720== Command: ./minishell
==1352720== 
minishell:/home/skanna/Documents/minishell$ <<lim | cat <<lim
> ^Cminishell:/home/skanna/Documents/minishell$  ^C
> minishell:/home/skanna/Documents/minishell$ exit
exit
==1352720== 
==1352720== FILE DESCRIPTORS: 3 open (3 std) at exit.
==1352720== 
==1352720== HEAP SUMMARY:
==1352720==     in use at exit: 208,381 bytes in 229 blocks
==1352720==   total heap usage: 1,214 allocs, 985 frees, 252,968 bytes allocated
==1352720== 
==1352720== 45 bytes in 1 blocks are definitely lost in loss record 15 of 67
==1352720==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1352720==    by 0x40C7CE: ft_strjoin (str_ops.c:91)
==1352720==    by 0x4013E9: get_dynamic_prompt (minishell.c:60)
==1352720==    by 0x40B26F: sigint_handler (handle_signals.c:20)
==1352720==    by 0x490B51F: ??? (in /usr/lib/x86_64-linux-gnu/libc.so.6)
==1352720==    by 0x49DD7E1: read (read.c:26)
==1352720==    by 0x40D156: check_read (get_next_line.c:88)
==1352720==    by 0x40D258: get_next_line (get_next_line.c:112)
==1352720==    by 0x4068C0: read_here_doc (get_fds.c:60)
==1352720==    by 0x4067E5: get_infile (get_fds.c:87)
==1352720==    by 0x406552: fill_fd_utils (fill_fds.c:60)
==1352720==    by 0x406429: fill_fd (fill_fds.c:83)
==1352720== 
==1352720== LEAK SUMMARY:
==1352720==    definitely lost: 45 bytes in 1 blocks
==1352720==    indirectly lost: 0 bytes in 0 blocks
==1352720==      possibly lost: 0 bytes in 0 blocks
==1352720==    still reachable: 0 bytes in 0 blocks
==1352720==         suppressed: 208,336 bytes in 228 blocks
==1352720== 
==1352720== For lists of detected and suppressed errors, rerun with: -s
==1352720== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

*/