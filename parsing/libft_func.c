/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:20:08 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/04 02:03:31 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*new_value;

	i = 0;
	new_value = (char *)my_alloc((ft_strlen(s1) + 1) * sizeof(char), 0);
	if (!new_value)
		return (NULL);
	while (s1[i])
	{
		new_value[i] = s1[i];
		i++;
	}
	new_value[i] = '\0';
	return (new_value);
}

char	*ft_strncpy(char *s, int len)
{
	char	*new_s;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	new_s = my_alloc(len + 1, 0);
	if (!new_s)
		return (NULL);
	while (i < len)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

int	str_chr(char *s, char c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((n > i) && (s1[i] == s2[i]) && (s1[i] != '\0'))
		i++;
	if (n == i)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return ;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}
