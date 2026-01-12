/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:30:15 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/04 02:09:26 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_if_quote(char *s, char qoute, int *i, int *counter)
{
	int	q;

	(*counter)++;
	(*i)++;
	q = 1;
	if (is_quotes(s[*i]))
	{
		(*i)++;
		return ;
	}
	while (s[*i] && !(q % 2 == 0 && is_withspaces(s[*i])))
	{
		if (s[*i] == qoute)
			q++;
		(*i)++;
	}
}

void	count_if_char(char *s, int *i)
{
	int	flag;
	int	q;

	q = 0;
	flag = -1;
	while (s[*i])
	{
		if (flag == -1 && s[*i] == DOUBLE_QUOTE)
		{
			q++;
			flag = 0;
		}
		if (flag == 0 && s[*i] == DOUBLE_QUOTE)
			q++;
		else if (flag == -1 && s[*i] == SINGLE_QUOTE)
		{
			q++;
			flag = 1;
		}
		if (flag == 1 && s[*i] == SINGLE_QUOTE)
			q++;
		if (is_withspaces(s[*i]) && (q % 2 != 0 || !q))
			break ;
		(*i)++;
	}
}

static int	count_words(char *s)
{
	int	counter;
	int	i;
	int	q;

	q = 0;
	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] && is_withspaces(s[i]))
			i++;
		if (s[i] && s[i] == DOUBLE_QUOTE)
			count_if_quote(s, DOUBLE_QUOTE, &i, &counter);
		else if (s[i] && s[i] == SINGLE_QUOTE)
			count_if_quote(s, SINGLE_QUOTE, &i, &counter);
		else if (s[i] && !is_withspaces(s[i]) && !is_quotes(s[i]))
		{
			counter++;
			count_if_char(s, &i);
		}
	}
	return (counter);
}

static char	*allocate_element(char **s, char **array, int j)
{
	int	i;

	i = 0;
	if (**s == SINGLE_QUOTE)
		return (ft_word((char *)(*s), array, j, SINGLE_QUOTE));
	else if (**s == DOUBLE_QUOTE)
		return (ft_word((char *)(*s), array, j, DOUBLE_QUOTE));
	else
		return (ft_word((char *)*s, array, j, DOUBLE_QUOTE));
	return (NULL);
}

char	**ft_split(char *s)
{
	char	**array;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	array = (char **)my_alloc((count_words((char *)s) + 1) * sizeof(char *), 0);
	if (!array)
		return (NULL);
	while (*s)
	{
		while (*s && is_withspaces(*s))
			s++;
		if (*s && !is_withspaces(*s))
		{
			array[j] = allocate_element(&s, array, j);
			if (array[j] == NULL)
				return (NULL);  //free(array),
			j++;
		}
		wait_till_end(&s);
	}
	array[j] = NULL;
	return (array);
}
