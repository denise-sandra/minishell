/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/12 15:14:47 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**pars_path(t_mini *mini)
{
	char	*path;
	char	**split_paths;

	path = get_env_value(mini->env, "PATH");
	check_malloc_error(mini, path, "Malloc in exectution",  -1);
	split_paths = ft_split(path, ':');
	if (!split_paths)
		return (NULL);
	free(path);
	return (split_paths);
}

static char	*join_path(t_mini *mini, char *cmd, char *path)
{
	char	*joint_a;
	char	*joint_b;

	joint_a = ft_strjoin_char(path, '/');
	check_malloc_error(mini, joint_a, "Malloc in exectution",  -1);
	joint_b = ft_strjoin(joint_a, cmd);
	check_malloc_error(mini, joint_b, "Malloc in exectution",  -1);
	free(joint_a);
	return (joint_b);
}

static int	process_line(t_mini *mini, char *line, char *eof,int i)
{
	size_t	line_len;
	size_t	eof_len;

	line_len = ft_strlen(line);
	eof_len = ft_strlen(eof);
	if (line_len > 0 && line[line_len - 1] == '\n')
	{
		line[line_len - 1] = '\0';
		line--;
	}
	if (ft_strncmp(line, eof, eof_len) == 0 && line_len == eof_len)
		return (free(line), 1);
	line[line_len] = '\n';
	line_len++;
	write(mini->fd_in[i], line, line_len);
	free(line);
	return (0);
}

static int	get_infile(t_mini *mini, t_token *token, int i)
{
	int		is_eof;
	char	*line;
	char	*eof;
	
	is_eof = 0;
	eof = NULL;
	if (token->type == IN)
	{
		mini->fd_in[i] =  open(token->next->value, O_RDONLY);
		if (mini->fd_in[i] < 0)
			return (ft_error("Can't open infile", mini), 1);
	}
	else if (token->type == HERE)
	{
		eof = token->next->value;
		while (is_eof == 0)
		{
			line = readline(STDIN_FILENO);
			if (!line)
				is_eof = 1;
			else
				is_eof = process_line(mini, line, eof, i);
		}
	}
	return (0);
}

static int	get_outfile(t_mini *mini, t_token *token, int i)
{
	if (token->type == OUT)
	{
		mini->fd_out[i] =  open(token->next->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (mini->fd_out[i] < 0)
			return (ft_error("Can't open outfile", mini), 1);
	}
	if (token->type == APP)
	{
		mini->fd_out[i] =  open(token->next->value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (mini->fd_out[i] < 0)
			return (ft_error("Can't open outfile", mini), 1);
	}
	return (0);
}

static void	cmd_exec(t_mini *mini, t_token *tmp)
{
	int	i;
	char	**paths;
	char	*path_with_token;

	i = 0;
	paths = pars_path(mini);
	if (paths == NULL)
		return (ft_error("Memory allocation error in execution", mini));
	while (paths[i])
	{
		path_with_token = join_path(mini, tmp->cmd_tab[0], paths[i]);
		if (access(path_with_token, X_OK) == 0)
		{
			if (execve(path_with_token, tmp->cmd_tab, mini->env_char) == -1)
				return (ft_error("execve Error", mini));
		}
		free(path_with_token);
		i++;
	}
	free(paths);
}

static void	ft_dup(t_mini *mini, int i)
{
	//printf("mini in: %i    mini out: %i\n", mini->fd_in[i], mini->fd_out[i]);
	if (mini->fd_in[i] != STDIN_FILENO)
	{
		if (dup2(mini->fd_in[i], STDIN_FILENO) == -1)
		{
			close(mini->fd_in[i]);
			ft_error("dup Error", mini);
		}
		close(mini->fd_in[i]);
	}
	if (mini->fd_out[i] != STDOUT_FILENO)
	{
		if (dup2(mini->fd_out[i], STDOUT_FILENO) == -1)
		{
			close(mini->fd_out[i]);
			ft_error("dup Error", mini);
		}
		close(mini->fd_out[i]);
	}
}

static void	fill_fd(t_mini *mini)
{
	t_token	*tmp;
	int		i;
	
	tmp = mini->token;
	i = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		if (get_infile(mini, tmp, i) != 0)
			return ;
		if (get_outfile(mini, tmp, i) != 0)
			return ;
		tmp = tmp->next;
	}
}

void	execution(t_mini *mini)
{
	t_token	*tmp;
	int		i;
	
	init_fds(mini);
	fill_fd(mini);
	i = 0;
	tmp = mini->token;
	while (tmp)
	{
		if (tmp->type == COMMAND)
		{
			mini->pid[i] = fork();
			if (mini->pid[i] < 0)
				return(ft_error("Fork error", mini));
			if (mini->pid[i] == 0)
			{
				ft_dup(mini, i);
				if (execute_builtin(mini, tmp->cmd_tab[0]) == 0)
					return ;
				else
					return (cmd_exec(mini, tmp));
			}
			i++;
		}
		tmp = tmp->next;
	}
	i = 0;
	while (i < mini->cmd_count)
	{
		if (mini->fd_in && mini->fd_in[i] != STDIN_FILENO)
			close(mini->fd_in[i]);
		if (mini->fd_out && mini->fd_out[i] != STDOUT_FILENO)
			close(mini->fd_out[i]);
		waitpid(mini->pid[i++], NULL, 0);
	}
		
}
