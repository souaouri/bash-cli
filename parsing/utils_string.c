/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:25:41 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/04 02:02:19 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src != '\0')
	{
		*ptr = *src;
		src++;
		ptr++;
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	else if (s1 == NULL)
		return (s2);
	else if (s2 == NULL)
		return (s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *) my_alloc(sizeof(char) * (s1_len + s2_len + 1), 0);
	if (result == NULL)
		return (NULL);
	ptr = ft_strcpy(result, s1);
	ptr = ft_strcpy(result + s1_len, s2);
	*(ptr + s2_len) = '\0';
	return (result);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while ((s1[i] == s2[i]) && (s1[i] != '\0') && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;
	size_t			j;
	size_t			s_len;

	j = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (s_len - start <= len)
		len = s_len - start;
	substr = (char *)my_alloc((len + 1) * sizeof(char), 0);
	if (!substr)
		return (NULL);
	while (s[i])
	{
		if (j < len && i >= start)
			substr[j++] = s[i];
		i++;
	}
	substr[j] = '\0';
	return (substr);
}
