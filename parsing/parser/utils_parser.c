/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:53:47 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/01 21:52:03 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_arrays(t_cmds *cmds)
{
	if (cmds)
	{
		cmds->args = NULL;
		cmds->cmmd = NULL;
		cmds->in_file = -2;
		cmds->out_file = -2;
		cmds->heredoc = -2;
		cmds->aout_file = -2;
		cmds->is_error = 0;
	}
}

int	get_lcmd(t_lexer *lexer)
{
	t_lexer	*tmp;
	int		counter;

	counter = 0;
	tmp = lexer;
	while (tmp)
	{
		if (tmp->token == mpipe)
			counter++;
		tmp = tmp->next;
	}
	return (counter);
}
