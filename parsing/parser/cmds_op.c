/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:16:43 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/04 02:02:31 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmds	*ft_lstlast_cmd(t_cmds *cmds)
{
	while (cmds)
	{
		if (!cmds->next)
			return (cmds);
		cmds = cmds->next;
	}
	return (cmds);
}

t_cmds	*ft_lstnew_cmd(void)
{
	t_cmds	*cmds;

	cmds = (t_cmds *)my_alloc(sizeof(t_cmds), 0);
	cmds->next = NULL;
	cmds->prev = NULL;
	cmds->cmd = NULL;
	cmds->stop_ex = -1;
	return (cmds);
}

int	ft_lstsize_cmd(t_cmds *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_lstadd_back_cmd(t_cmds **cmds, t_cmds *new)
{
	t_cmds	*last;

	if (!cmds)
		return ;
	if (*cmds)
	{
		last = ft_lstlast_cmd(*cmds);
		last->next = new;
		new->prev = last;
	}
	else
		*cmds = new;
}
