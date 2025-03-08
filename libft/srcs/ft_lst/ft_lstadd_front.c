/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
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
//helper function: print_lst
void	ft_print_list(t_list *lst)
{
	while (lst != NULL)
	{
		//casts the void *content of the current node to a char * (character pointer)
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}
*/
/*
int main()
{
	// Start with an empty list
	t_list *head = NULL;
	t_list *node1 = ft_lstnew("1st node content [LAST!]");
	t_list *node2 = ft_lstnew("2nd node content");
	t_list *node3 = ft_lstnew("3rd node content [FIRST!]");
	// Add nodes to the front of the list
	ft_lstadd_front(&head, node1); //head pointed to node1
	ft_lstadd_front(&head, node2); //head is updated to point to node2
	ft_lstadd_front(&head, node3); //head is updated to point to node3
	//ft_lstadd_front => add each new node to the front of the list
	//ORDER: head -> node3 -> node2 -> node1 -> NULL

	// Print the list
	ft_print_list(head);
	// Free the list nodes
	t_list *temp;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	return (0);
}
*/
