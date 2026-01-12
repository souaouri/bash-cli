/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:21:22 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/04 02:17:00 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(char *s, char c)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			counter++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (counter);
}

static char	*my_word(char *s, char c, char **arr, int ind)
{
	int		i;
	char	*output;
	int		j;
	(void)arr;
	(void)ind;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	output = (char *)my_alloc(sizeof(char) * (i + 1), 0);
	if (!output)
	// {
	// 	while (j < ind)
	// 		free(arr[j++]);
		return (NULL);
	// }
	i = 0;
	while (s[i] && s[i] != c)
	{
		output[i] = s[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	**my_split(char const *s, char c)
{
	char	**array;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	array = (char **)my_alloc((count_words((char *)s, c) + 1) * sizeof(char *), 0);
	if (!array)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			array[j] = my_word((char *)s, c, array, j);
			if (array[j] == NULL)
				(free(array), (void) NULL);
			j++;
		}
		while (*s && *s != c)
			s++;
	}
	array[j] = 0;
	return (array);
}
