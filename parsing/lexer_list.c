/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:16:49 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/04 02:08:16 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_lstlast(t_lexer *lexer)
{
	while (lexer)
	{
		if (!lexer->next)
			return (lexer);
		lexer = lexer->next;
	}
	return (lexer);
}

t_lexer	*ft_lstnew(int content)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)my_alloc(sizeof(t_lexer), 0);
	if (!lexer)
		return (NULL);
	lexer->i = content;
	lexer->next = NULL;
	lexer->prev = NULL;
	return (lexer);
}

int	ft_lstsize(t_lexer *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_lstadd_back(t_lexer **lexer, t_lexer *new)
{
	t_lexer	*last;

	if (!lexer)
		return ;
	if (*lexer)
	{
		last = ft_lstlast(*lexer);
		last->next = new;
		new->prev = last;
	}
	else
		*lexer = new;
}

void	ft_lst_remove(t_lexer **lexer, int index)
{
	t_lexer	*tmp;
	t_lexer	*tmp2;

	tmp = *lexer;
	if (!lexer)
		return ;
	while (tmp)
	{
		if (tmp->i == index)
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			tmp2 = tmp->next;
			if (tmp->i == 0 && ft_lstsize(*lexer) >= 1)
				*lexer = tmp->next;
			// free(tmp);
			break ;
		}
		tmp = tmp->next;
	}
}
