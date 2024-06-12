/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/12 09:26:28 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_command(int infile, t_bonus *cmd, char **split_paths, int argc)
{
	close(cmd->tube[0][0]);
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		close(infile);
		error_bonus("dup error", cmd, split_paths, argc);
	}
	close(infile);
	if (dup2(cmd->tube[0][1], STDOUT_FILENO) == -1)
		error_bonus("dup error", cmd, split_paths, argc);
	close(cmd->tube[0][1]);
	command_exc(cmd, split_paths, argc);
	error_bonus("Command not found", cmd, split_paths, argc);
}

void	middle_command(t_bonus *cmd, char **split_paths, int argc)
{
	int	j;

	j = 0;
	while (j < cmd->i)
		close(cmd->tube[j++][1]);
	close(cmd->tube[cmd->i][0]);
	if (dup2(cmd->tube[cmd->i - 1][0], STDIN_FILENO) == -1)
		error_bonus("dup error", cmd, split_paths, argc);
	j = 0;
	while (j < cmd->i)
		close(cmd->tube[j++][0]);
	if (dup2(cmd->tube[cmd->i][1], STDOUT_FILENO) == -1)
		error_bonus("dup error", cmd, split_paths, argc);
	close(cmd->tube[cmd->i][1]);
	command_exc(cmd, split_paths, argc);
	error_bonus("Command not found", cmd, split_paths, argc);
}

void	last_command(int outfile, t_bonus *cmd, char **split_paths, int argc)
{
	int	j;

	j = 0;
	while (j < argc - 4)
		close(cmd->tube[j++][1]);
	if (dup2(cmd->tube[cmd->i - 1][0], STDIN_FILENO) == -1)
	{
		close(outfile);
		error_bonus("dup error", cmd, split_paths, argc);
	}
	j = 0;
	while (j < argc - 4)
		close(cmd->tube[j++][0]);
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		close(outfile);
		error_bonus("dup error", cmd, split_paths, argc);
	}
	close(outfile);
	command_exc(cmd, split_paths, argc);
	error_bonus("Command not found", cmd, split_paths, argc);
}