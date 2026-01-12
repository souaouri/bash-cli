/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:07:26 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/02 10:03:20 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_handel_options(char **str, t_lexer ***tmp)
{
	if (!str[0])
	{
		(**tmp)->str = ft_strdup("");
		return (0);
	}
	if (str[1] == NULL)
	{
		(**tmp)->str = str[0];
		return (0);
	}
	(**tmp)->str = ft_strdup(str[0]);
	return (1);
}

void	handle_options(t_lexer **tmp, t_env **env_list)
{
	char	**str;
	t_lexer	*tmp2;
	t_lexer	*node;
	int		i;

	i = 2;
	str = my_split(expanding_str(tmp, env_list), 32);
	if (init_handel_options(str, &tmp) == 0)
		return ;
	node = ft_lstnew((*tmp)->i++);
	node->str = ft_strdup(str[1]);
	node->token = word;
	node->prev = *tmp;
	(*tmp)->next = node;
	tmp2 = node;
	while (str[i] != NULL)
	{
		node = ft_lstnew((*tmp)->i++);
		node->str = ft_strdup(str[i]);
		node->token = word;
		node->prev = tmp2;
		tmp2->next = node;
		tmp2 = node;
		i++;
	}
}

void	expanding_cases(t_lexer **tmp, t_env **env_list)
{
	if ((*tmp)->str[0] == '$' && ((*tmp)->str[1] == DOUBLE_QUOTE || \
		(*tmp)->str[1] == SINGLE_QUOTE))
		(*tmp)->str = ft_substr((*tmp)->str, 1, ft_strlen((*tmp)->str) - 1);
	if ((*tmp)->token == word && ((*tmp)->str && (*tmp)->str[0] == '$'))
		handle_options(&(*tmp), env_list);
	else
		(*tmp)->str = expanding_str(tmp, env_list);
	if ((*tmp)->token != word)
		(*tmp)->str = ft_strdup("");
	if (!(*tmp)->str && (*tmp)->has_q == 1)
		(*tmp)->str = ft_strdup("");
}

void	*find_dollar(char *result, char *s, int *i)
{
	int	k;

	if (!result)
		return (NULL);
	k = *i;
	while (s && s[*i] && s[*i] != DOUBLE_QUOTE)
		i++;
	result = ft_strjoin(result, ft_substr(s, k, (*i) - k + 1));
	return (result);
}

int	check_if_noexpand(t_lexer **tmp)
{
	if (str_chr((*tmp)->str, '$') == -1 || (*tmp)->token == delimiter)
		return (1);
	if ((*tmp)->str[0] == '$' && is_number((*tmp)->str[1]) && \
		ft_strlen((*tmp)->str) != 2)
	{
		(*tmp)->str = ft_substr((*tmp)->str, 2, ft_strlen((*tmp)->str));
		return (1);
	}
	return (0);
}
