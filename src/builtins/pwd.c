/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:20 by skanna            #+#    #+#             */
/*   Updated: 2024/07/03 18:39:08 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(t_mini *mini)
{
	char	cwd[1024];
	int		size;

	size = 1024;
	if (getcwd(cwd, size) == NULL)
		return (ft_error(mini, NULL, strerror(errno)));
	printf("%s\n", cwd);
}
