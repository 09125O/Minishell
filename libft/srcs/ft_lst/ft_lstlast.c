/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
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

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

/* METHOD B: create another variable, keep "lst" unchanged
t_list	*ft_lstlast(t_list *lst)
{
	t_list *last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}
*/
/*
//helper function: lstnew
t_list *ft_lstnew(void *content)
{
	t_list *new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
=============TEST MAIN============================
int main()
{
	// Start with an empty list
	// Add nodes to the front of the list
	t_list *head = ft_lstnew(NULL);
	t_list *node1 = ft_lstnew("1st node content");
	t_list *node2 = ft_lstnew("2nd node content");
	t_list *node3 = ft_lstnew("3rd node content");
	t_list *node4 = ft_lstnew("4th node content");
	t_list *node5 = ft_lstnew("5th HERE'S THE LAST CONTENT!");
	
	head = node1;
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;

	// Print the list
	t_list *last = ft_lstlast(head);
	printf("%s\n", (char *)last->content);
	return (0);
}
*/
