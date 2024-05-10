/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:55 by skanna            #+#    #+#             */
/*   Updated: 2024/05/10 16:35:46 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structures.h"
# include "../libft/Includes/libft_extended.h"


typedef struct s_minishell
{
	t_environement	env;
	t_token			*tokens;
	int				token_count;
	int				last_exit_status;
	int				redirect_in;
	int				redirect_out;
	char			*input_file;
	char			*output_file;
}	t_minishell;

//src
void    env_fill_structure(char **envp);

//utils
void    ft_error(char *msg);
char    **ft_split_1st_token(char const *s, char c);

#endif