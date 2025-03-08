/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
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
#include <stdio.h>

typedef struct s_list
{
void *content;
struct s_list *next;
} t_list;

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
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
}
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst || !del || !(*lst))
		return ;
	ft_lstclear(&(*lst)->next, del);
	(del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}
//(f) function : Assuming content is integer => double the value
void	*dup_content(void *content)
{
	int	*new_content = (int *)malloc(sizeof(int));
	if (new_content)
		*new_content = *(int *)content * 2;
	return (new_content);
}
//(del) function: Delete the content of a node.
void	delete_content(void *content)
{
	free(content);
}
//check if NULL
// Iterate over each element of the original list
// Apply the function 'f' to the content of the current node
// Create a new node with the result of 'f'
// If creating a new node fails (e.g., due to memory allocation failure)
//free result using 'del'
//Clear any part of the new list created so far
// Add the new node to THE END of the new list		
// Move to the next node in the original list
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*set;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		set = f(lst->content);
		new_node = ft_lstnew(set);
		if (!new_node)
		{
			del(set);
			ft_lstclear(&new_list, (*del));
			return (new_list);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
// Create a linked list with integer contents.
//dereference + cast
//add a new node to the end of the list
// Call ft_lstmap with the list-> dup + delete
// Iterate mapped list + print the new contents
// Clean up the original list.
// Clean up the mapped list.
int main()
{
	t_list	*mapped_list;
	t_list	*mapped_first;
	t_list	*first = ft_lstnew(malloc(sizeof(int)));
	t_list	*second = ft_lstnew(malloc(sizeof(int)));
	*(int *)(first->content) = 1;
	*(int *)(second->content) = 2;
	ft_lstadd_back(&first, second);

	mapped_list = ft_lstmap(first, &dup_content, &delete_content);

	mapped_first = mapped_list;
	while (mapped_first)
	{
		printf("%i\n", *(int *)mapped_first->content);
		mapped_first = mapped_first->next;
	}
	ft_lstclear(&first, &delete_content);
	ft_lstclear(&mapped_list, &delete_content);
	return (0);
}
*/