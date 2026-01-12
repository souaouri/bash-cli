/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:00:13 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/04 02:01:12 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	len_of_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i + 1);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] && --dstsize >= 0)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (j);
}

char	**change_a_sto_d_ptr(char *cmd)
{
	char	**ptr;
	int		len;

	len = ft_strlen(cmd);
	ptr = (char **)my_alloc(2 * sizeof(char *), 0);
	ptr[0] = (char *)my_alloc(len + 1, 0);
	ft_strlcpy(ptr[0], cmd, len);
	ptr[0][len] = '\0';
	ptr[1] = NULL;
	return (ptr);
}

char	**join_cmd_arg(char *cmd, char **arg)
{
	int		i;
	int		j;
	char	**ptr;

	ptr = NULL;
	i = 0;
	j = 0;
	if (cmd == NULL && arg == NULL)
		return (NULL);
	else if (cmd == NULL)
		return (arg);
	else if (arg == NULL)
		return (change_a_sto_d_ptr(cmd));
	ptr = my_alloc(sizeof(char *) * (len_of_arg(arg) + 1), 0);
	ptr[0] = cmd;
	i++;
	while (arg[j])
	{
		ptr[i] = arg[j];
		i++;
		j++;
	}
	ptr[i] = NULL;
	return (ptr);
}

int	ambugious(t_cmds **list)
{
	if ((*list)->is_ambugious == 1)
	{
		*list = (*list)->next;
		return (1);
	}
	return (0);
}
