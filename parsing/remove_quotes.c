/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:42:57 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/04 02:02:04 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_mlen(char *s, char q)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != q)
			len++;
		i++;
	}
	return (len);
}

void	*remove_each_one(char *s, char q)
{
	int		len;
	int		i;
	char	*new_s;
	int		j;

	j = 0;
	i = 0;
	len = get_mlen(s, q);
	new_s = my_alloc(len + 1, 0);
	i = 0;
	while (s[i] && j < len)
	{
		if (s[i] != q)
			new_s[j++] = s[i];
		i++;
	}
	new_s[j] = '\0';
	return (new_s);
}

void	remove_quotes(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp)
	{
		if (has_q(tmp->str) == 1 && !tmp->expanded)
			tmp->str = remove_each_one(tmp->str, DOUBLE_QUOTE);
		else if (has_q(tmp->str) == 2 && !tmp->expanded)
			tmp->str = remove_each_one(tmp->str, SINGLE_QUOTE);
		tmp = tmp->next;
	}
}
