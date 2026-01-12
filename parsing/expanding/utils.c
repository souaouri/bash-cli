/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:14:56 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/02 09:45:26 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_real_char(char *s, int i)
{
	if (i != 0 && s[i - 1] == '?')
		return (0);
	return ((s[i] >= '0' && s[i] <= '9') || \
		(s[i] >= 'a' && s[i] <= 'z') || \
		(s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_' || s[i] == '?');
}

int	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

int	end_of_proccessing(char *s, int i)
{
	return (s[i] == '$' || s[i] == DOUBLE_QUOTE || \
		s[i] == SINGLE_QUOTE || s[i] == '\0' || \
			(i != 0 && s[i - 1] == '?'));
}

int	get_len_ep(char *s)
{
	int	len;

	len = 0;
	while (s[len] && !end_of_proccessing(s, len))
		len++;
	return (len);
}

int	init_expand(char *s, int *i, int *cnt)
{
	*cnt = 0;
	if (!ft_strcmp(s, "$"))
		return (0);
	while (s[*i] && s[*i] != '$')
		(*i)++;
	return (1);
}
