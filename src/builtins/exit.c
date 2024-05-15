/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:38:05 by skanna            #+#    #+#             */
/*   Updated: 2024/05/15 21:43:12 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	ft_atoll(const char *str, int *err)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
		{
			*err = 1;
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}


static void	is_arg_valid(t_minishell *minishell, char *exit_arg, int sign)
{
	int			i;
	long long	arg;
	int			err;

	i = 0;
	err = 0;
	while (exit_arg[i])
	{
		if (ft_isdigit(exit_arg[i]))
			i++;
		else
		{
			minishell->last_exit_status = 2;
			write (2, "Wrong arguments\n", 17);
			return ;
		}
	}
	arg = ft_atoll(exit_arg, &err) * sign;
	if (err || arg < LLONG_MIN + 1 || arg > LLONG_MAX)
	{
		minishell->last_exit_status = 2;
		write(2, "Wrong arguments\n", 17);
		return ;
	}
	if (arg < 0)
		arg = 256 + (arg % 256);
	minishell->last_exit_status = (arg % 256);
}

static void	is_var_valid(t_minishell *minishell, char *var_name)
{
	char	*var_value;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	var_value = get_env_value(minishell->env, var_name);
	if (var_value == NULL)
	{
		minishell->last_exit_status = 0;
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

void	exit_cmd(t_minishell *minishell, char *input)
{
	int	i;
	int	sign;

	printf("exit\n");
	i = 0;
	sign = 1;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
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
			minishell->last_exit_status = 2;
			write (2, "minishell: wrong argument\n", 27);
			return ;
		}
	}
}
