/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:57:36 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/02 09:57:37 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_cmd(t_lexer *node)
{
	t_lexer	*newnode;

	newnode = node;
	while (newnode)
	{
		if (node->token == word)
			return (1);
		newnode = node->prev;
	}
	return (0);
}

void	found_pipe( t_lexer **node, int **is_hdc, int **is_file)
{
	(*node)->token = mpipe;
	*is_hdc = 0;
	*is_file = 0;
}

void	check_redir(char *res, t_lexer *node, int *is_hdc, int *is_file)
{
	if (!ft_strcmp(res, ">>"))
		node->token = redirect_app;
	else if (!ft_strcmp(res, "|"))
		found_pipe(&node, &is_hdc, &is_file);
	else if (!ft_strcmp(res, ">"))
		node->token = redirect_out;
	else if (!ft_strcmp(res, "<"))
		node->token = redirect_in;
	else if (!ft_strcmp(res, "<<"))
	{
		node->token = heredoc;
		*is_hdc = 1;
	}
	else if (*is_hdc)
	{
		node->token = delimiter;
		*is_hdc = 0;
	}
	else if (*is_file)
	{
		node->token = file;
		*is_file = 0;
	}
	else
		node->token = word;
}

void	tokenizer(char **res, t_lexer **lexer)
{
	int		i;
	int		is_heredoc;
	int		is_file;
	t_lexer	*node;

	is_heredoc = 0;
	is_file = 0;
	i = 0;
	while (res[i])
	{
		node = ft_lstnew(i);
		check_redir(res[i], node, &is_heredoc, &is_file);
		if ((!ft_strcmp(res[i], "<")) || (!ft_strcmp(res[i], ">")) || \
			(!ft_strcmp(res[i], ">>")))
			is_file = 1;
		node->str = res[i];
		node->expanded = 0;
		ft_lstadd_back(lexer, node);
		i++;
	}
}
