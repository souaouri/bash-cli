/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addresses_collector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:26:41 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/04 09:08:08 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_add_collector(t_addresses **lst, t_addresses *new)
{
	t_addresses	*ptr;

	if (!*lst || !lst)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	ptr = *lst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	new->next = NULL;
}

t_addresses	*ft_lstnew_add_collector(char *line)
{
	t_addresses	*new;

	new = malloc(sizeof(t_addresses));
	if (!new)
		return (NULL);
	new->content = line;
	new->next = NULL;
	return (new);
}

// void	*my_alloc(size_t size)
// {
// 	static t_addresses	*gooper;
// 	t_addresses			*node;
// 	void				*address;

// 	address = malloc(size);
// 	if (!address)
// 		(perror("malloc"), exit(1));
// 	if (gooper == NULL)
// 		gooper = ft_lstnew_add_collector(address);
// 	else
// 	{
// 		node = ft_lstnew_add_collector(address);
// 		ft_lstadd_back_add_collector(&gooper, node);
// 	}
// 	return (address);
// }

void free_list(t_addresses **list)
{
    t_addresses *temp;

    while (*list)
    {
		//printf("%s\n", (*list)->content);
        temp = *list;
        *list = (*list)->next;
        free(temp->content);  // Free the content
        free(temp);           // Free the node
    }
    *list = NULL;
}

void    *my_alloc(size_t size, int free)
{
    static t_addresses    *gooper = NULL;
    t_addresses            *node;
    void                *address;
    
    if (gooper && free == 1)
    {
        free_list(&gooper);
        return (NULL);
    }
    address = malloc(size);
    if (!address)
        (perror("malloc"), exit(1));
    if (gooper == NULL)
        gooper = ft_lstnew_add_collector(address);
    else
    {
        node = ft_lstnew_add_collector(address);
        ft_lstadd_back_add_collector(&gooper, node);
    }
    return (address);
}