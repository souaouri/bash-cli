/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:11:06 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/02 10:03:20 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirs(t_lexer *lexer)
{
	return (lexer->token >= 2 && lexer->token <= 6);
}

int	is_withspaces(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_quotes(char c)
{
	return (c == DOUBLE_QUOTE || c == SINGLE_QUOTE);
}

int	has_q(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == DOUBLE_QUOTE)
			return (1);
		else if (s[i] == SINGLE_QUOTE)
			return (2);
		i++;
	}
	return (0);
}

int	no_quotes(char *line, int i)
{
	if (i != 0 && (line[i] == DOUBLE_QUOTE || line[i] == SINGLE_QUOTE))
		return (1);
	return (0);
}
