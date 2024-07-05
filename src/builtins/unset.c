/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/07/05 08:55:33 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_cmd_utils(t_mini *mini, t_token *cur, int i)
{
	t_lst_env	*prev;
	t_lst_env	*tmp;
	size_t		len;

	len = ft_strlen(cur->cmd_tab[i]);
	tmp = mini->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, cur->cmd_tab[i], len) == 0)
		{
			if (prev == NULL)
				mini->env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			tmp = NULL;
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

/*
Atentcion aqui hay leaks cuando se llama a variables que han sido unset:
inishell$ unset SHELL
minishell$ env | grep SHELL

==1534582== 3,948 bytes in 67 blocks are definitely lost in loss record 48 of 71
==1534582==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1534582==    by 0x40780E: ft_strjoin_free (ft_strjoin_free.c:31)
==1534582==    by 0x407226: join_env (list_to_tab.c:29)
==1534582==    by 0x4070F9: list_to_tab (list_to_tab.c:48)
==1534582==    by 0x406815: unset_cmd (unset.c:58)
==1534582==    by 0x404625: execute_builtin (execute_builtin.c:51)
==1534582==    by 0x4040D5: builtin_in_parent (execution.c:95)
==1534582==    by 0x404015: execution (execution.c:109)
==1534582==    by 0x4012BC: parse_and_execute (minishell.c:42)
==1534582==    by 0x401476: minishell (minishell.c:61)
==1534582==    by 0x401344: main (minishell.c:78)

Tambien, cuando se hace unset de una variable que no existe, el error debe ser 0 no 1:
minishell$ unset TES
minishell$ echo $?
1

*/

void	unset_cmd(t_mini *mini, t_token *cur)
{
	int		i;
	int		changed;

	i = 1;
	changed = 0;
	while (cur->cmd_tab[i])
	{
		changed = unset_cmd_utils(mini, cur, i);
		i++;
	}
	if (changed == 1)
	{
		free_tab(mini->env_char);
		mini->env_char = list_to_tab(mini);
	}
	mini->exit_status = 0;
}
