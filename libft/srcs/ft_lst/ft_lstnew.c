/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stddef.h>
#include <stdlib.h>

// structure to represent a node of your list
typedef struct s_list
{
void *content;
struct s_list *next;
} t_list;
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

/*
"->" operator is used to assign values to the members of a node 
in a linked list when the node is being accessed through a pointer.

return(new):
allow the calling function to receive the pointer to the newly created node, 
so it can be used or linked into a data structure, such as a linked list.

========================MAIN================

#include <stdlib.h>
#include <stdio.h>
int main()
{
	// Create a new node with some content
	int	a = 42;
	//Create a node with address of 'a'
	t_list *node;
	node = ft_lstnew(&a);
	// Check if the node was created successfully
	if (node == NULL)
	{
		printf("Memory allocation FAIL!\n");
		return (1);
	}
	// Dereference the content pointer to get the integer value
    // (int *)(node->content) casts the void pointer to an int pointer
    // *(int *)(node->content) dereferences the int pointer to get the int value
	printf("Memory content: %i\n", *(int *)(node->content));
	free(node);
	return (0);
}
*/
