/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utile_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:39:47 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/04 02:00:05 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*print_quotes(char *var, int i, int size)
{
	int		j;
	int		x;
	char	*ptr;

	j = 0;
	x = 0;
	ptr = my_alloc(sizeof(char) * size + 1, 0);
	while (var[i])
	{
		if (var[i] == '=' && x == 0)
		{
			ptr[j] = '=';
			j++;
			ptr[j] = '\"';
			j++;
			i++;
			x++;
		}
		if (var[i] != '\0')
			ptr[j++] = var[i++];
	}
	if (x != 0)
		ptr[j++] = '\"';
	ptr[j] = '\0';
	return (ptr);
}

char	*add_double_quotes(char *var)
{
	int		i;
	int		j;
	int		x;
	int		size;
	char	*ptr;

	size = ft_strlen(var);
	i = 0;
	j = 0;
	x = 0;
	if (ft_strchr(var, '='))
		size += 2;
	ptr = my_alloc(sizeof(char) * size + 1, 0);
	if (var[0] == '\0' || var == NULL)
		return (NULL);
	ptr = print_quotes(var, i, size);
	return (ptr);
}

void	ft_sort_env(t_env *env)
{
	char	**ptr;
	char	*tmp;
	int		list_len;
	int		i;
	t_env	*head;

	ptr = NULL;
	list_len = ft_lstsize_env(env);
	i = 0;
	while (i < list_len)
	{
		head = env;
		while (head->next)
		{
			if (ft_strcmp(head->content, head->next->content) > 0)
			{
				tmp = head->content;
				head->content = head->next->content;
				head->next->content = tmp;
			}
			head = head->next;
		}
		i++;
	}
	head = NULL;
}

char	*get_var_from_beg_to_eq(char *var)
{
	int		i;
	char	*ptr;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	ptr = (char *)my_alloc(i + 1, 0);
	i = 0;
	if (ft_strchr(var, '+'))
	{
		while (var[i] && var[i + 1] != '=')
		{
			ptr[i] = var[i];
			i++;
		}
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*get_eq_to_fin(char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (NULL);
	if (ft_strchr(var, '='))
	{
		while (var[i] && var[i] != '=')
			i++;
		if (var[i] == '=')
			i++;
	}
	return (var + i);
}
