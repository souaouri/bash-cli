/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:28:01 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/02 11:00:35 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_to_print_exit(int len)
{
	if (len > 1)
		return (1);
	else
		return (0);
}

void	initialize_files(t_cmds **list)
{
	t_cmds	*tmp;

	tmp = *list;
	if (tmp == NULL)
		return ;
	if (tmp->heredoc > 2)
		tmp->in_file = tmp->heredoc;
	if (tmp->in_file == -2)
		tmp->in_file = 0;
	if (tmp->aout_file > tmp->out_file)
		tmp->out_file = tmp->aout_file;
	if (tmp->out_file == -2 && tmp->aout_file == -2)
		tmp->out_file = 1;
}
