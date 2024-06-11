/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:38:05 by skanna            #+#    #+#             */
/*   Updated: 2024/06/09 13:45:42 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	verify_spaces(t_mini *minishell, char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '\0')
	{
		minishell->exit_status = 0;
		return (0);
	}
	return (i);
}

static void	is_arg_valid(t_mini *minishell, char *exit_arg, int sign)
{
	long long	arg;
	int			err;

	err = 0;
	arg = ft_atoll(exit_arg, &err) * sign;
	if (err || arg < LLONG_MIN + 1 || arg > LLONG_MAX)
	{
		minishell->exit_status = 255;
		write(2, "Wrong arguments\n", 17);
		return ;
	}
	if (arg < 0)
		arg = 256 + (arg % 256);
	minishell->exit_status = (arg % 256);
}

static void	is_var_valid(t_mini *minishell, char *var_name)
{
	char	*var_value;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	var_value = get_env_value(minishell->env, var_name);
	if (var_value == NULL)
	{
		minishell->exit_status = 0;
		return ;
	}
	else
	{
		if (var_value[i] == '-')
			sign = -1;
		if (var_value[i] == '-' || var_value[i] == '+')
			is_arg_valid(minishell, var_value + ++i, sign);
		if (ft_isdigit(var_value[i]))
			is_arg_valid(minishell, var_value + i, sign);
	}
}

void	exit_cmd(t_mini *minishell, char *input)
{
	int	i;
	int	sign;

	printf("exit\n");
	sign = 1;
	i = verify_spaces(minishell, input);
	if (i == 0)
		return ;
	while (input[i])
	{
		if (input[i] == '-')
			sign = -1;
		if (input[i] == '-' || input[i] == '+')
			return (is_arg_valid(minishell, input + ++i, sign));
		if (input[i] == '$')
			return (is_var_valid(minishell, input + ++i));
		if (ft_isdigit(input[i]))
			return (is_arg_valid(minishell, input + i, sign));
		else
		{
			minishell->exit_status = 255;
			write (2, "minishell: wrong argument\n", 27);
			return ;
		}
	}
}
