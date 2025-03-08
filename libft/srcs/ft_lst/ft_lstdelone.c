/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stddef.h> //for the definition of the NULL pointer, size_t type
#include <stdlib.h>
#include <stdio.h>
typedef struct s_list
{
void *content;
struct s_list *next;
} t_list;
*/

/*delete a single node from a linked list. */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(del)(lst->content);
	free(lst);
	lst = NULL;
}
/*
If del = NULL, 
	=> no function provided to free the content, 
	=> function should not proceed because it could lead to memory leaks.
Deallocates the memory of the node itself. 
	After the content has been properly deallocated by the del function, 
	the structure holding the node can be safely freed.
To fully prevent dangling pointers,
	the pointers in the calling context should also be set to NULL,
	after the deletion function is called.
*/
