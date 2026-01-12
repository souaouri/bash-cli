/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:11:41 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/04 02:02:37 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*save_args(t_lexer **lexer, t_cmds *cmds)
{
	t_lexer	*tmp;
	int		len;
	int		i;

	i = 0;
	len = 0;
	tmp = *lexer;
	while (tmp && tmp->token == word)
	{
		len++;
		tmp = tmp->next;
	}
	cmds->args = my_alloc((len + 1) * sizeof(char *), 0);
	if (!cmds->args)
		return (NULL);
	while (i < len)
	{
		cmds->args[i] = ft_strdup((*lexer)->str);
		(*lexer) = (*lexer)->next;
		i++;
	}
	cmds->args[i] = NULL;
	return (lexer);
}

void	*handel_cmd_sec(t_lexer **tmp, t_cmds **cmds, int *j)
{
	t_lexer	*tmp2;

	if ((*j == 0 && (*tmp)->token == word) || \
		((*tmp)->token == word && (*tmp)->prev->token == mpipe))
	{
		(*cmds)->cmd = ft_strdup((*tmp)->str);
		if (!(*cmds)->cmd)
			return (NULL);
		(*tmp) = (*tmp)->next;
	}
	tmp2 = *tmp;
	if (tmp2 && tmp2->token != word && tmp2->token != mpipe)
	{
		while (tmp2 && tmp2->token != word && tmp2->token != mpipe)
			tmp2 = tmp2->next;
	}
	if (tmp2 && (tmp2)->token == word)
	{
		*tmp = tmp2;
		if (save_args(tmp, *cmds) == NULL)
			return (NULL);
	}
	return (*cmds);
}

void	*handel_cmd(t_lexer **tmp, t_cmds *cmds, int *j)
{
	t_lexer	*tmp2;

	tmp2 = *tmp;
	if (tmp2->token != word)
	{
		while (tmp2)
		{
			if (tmp2 && tmp2->token == word)
			{
				cmds->cmd = ft_strdup(tmp2->str);
				if (!cmds->cmd)
					return (NULL);
				tmp2 = tmp2->next;
				break ;
			}
			tmp2 = tmp2->next;
		}
		if (tmp2 && (tmp2)->token == word)
			if (save_args(&tmp2, cmds) == NULL)
				return (NULL);
	}
	else
		return (handel_cmd_sec(tmp, &cmds, j));
	return (cmds);
}

t_cmds	*get_node_parse(t_lexer **tmp, t_env **env)
{
	int		j;
	t_cmds	*node;

	j = 0;
	node = ft_lstnew_cmd();
	node->is_ambugious = 0;
	init_arrays(node);
	while (tmp && *tmp && (*tmp)->token != mpipe)
	{
		if (!handel_cmd(tmp, node, &j))
			return (NULL);
		if (handel_files(tmp, node, env) == -1)
			return (NULL);
		if (*tmp && (*tmp)->token == mpipe)
		{
			*tmp = (*tmp)->next;
			break ;
		}
		j++;
	}
	return (node);
}

void	*parser(t_lexer **lexer, t_cmds **cmds, int len, t_env **env)
{
	int		i;
	t_lexer	*tmp;
	t_cmds	*node;

	node = *cmds;
	tmp = *lexer;
	i = 0;
	while (tmp && i <= len)
	{
		node = get_node_parse(&tmp, env);
		if (!node)
			return (NULL);
		ft_lstadd_back_cmd(cmds, node);
		i++;
	}
	return (*cmds);
}
