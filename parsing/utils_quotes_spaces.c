/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:14:39 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/26 14:53:42 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_quote(int *i, char *line, int q, int *flag)
{
	(*i)++;
	*flag = 0;
	while (line[*i])
	{
		if (line[*i] == q)
		{
			*flag = 1;
			break ;
		}
		(*i)++;
	}
}

int	check_quotes(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (line[i])
	{
		if (line[i] == DOUBLE_QUOTE)
			check_quote(&i, line, DOUBLE_QUOTE, &flag);
		else if (line[i] == SINGLE_QUOTE)
			check_quote(&i, line, SINGLE_QUOTE, &flag);
		if (!line[i])
			break ;
		i++;
	}
	return (flag);
}

int	handel_quotes(char *line)
{
	if (!check_quotes(line))
		return (0);
	return (1);
}

int	is_redir_has_found(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

void	set_redir(char *s, int *j, int *i, char c)
{
	s[*j] = c;
	(*j)++;
	s[*j] = c;
	(*i)++;
}
