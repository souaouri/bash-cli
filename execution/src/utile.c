/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:28:03 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/04 01:30:00 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	multiple_cmd_util_5(t_cmds *list, int p_in, int p_out)
{
	if (list->in_file == 0)
		close(p_in);
	if (list->out_file == 1)
		close(p_out);
}

void	multiple_cmd_util_6(int p_in, int p_out)
{
	dup2(p_in, 0);
	close (p_in);
	dup2(p_out, 1);
	close (p_out);
}

void	reducing(t_cmds *list, int *hold_fd_in)
{
	change_list(list);
	multiple_cmd_util_1(list->in_file, hold_fd_in);
	multiple_cmd_util_2(hold_fd_in);
	multiple_cmd_util_3(list, hold_fd_in);
	multiple_cmd_util_4(list);
}

int	initialize_var(t_var **var, t_cmds *list)
{
	if (!list)
		return (0);
	if (list->cmd == NULL)
	{
		if (list->in_file > 0)
			close(list->in_file);
		if (list->out_file > 1)
			close(list->out_file);
	}
	(*var)->hold_fd_in = 0;
	(*var)->exit_status = 0;
	(*var)->i = 0;
	(*var)->util = NULL;
	(*var)->pid = 1;
	return (1);
}

void	multiple_cmd_util_7(t_var **var, t_cmds **list, int len)
{
	if ((*var)->pid < 0)
		print_error(NULL, "fork");
	multiple_cmd_util_6((*var)->p_in, (*var)->p_out);
	*list = (*list)->next;
	if ((*var)->pid == 0 && len != 1)
		exit(0);
}
