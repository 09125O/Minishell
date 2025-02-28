/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:25:03 by niperez           #+#    #+#             */
/*   Updated: 2024/06/04 16:58:14 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_lst(t_list *head, void (*del)(void *), void *content)
{
	del(content);
	ft_lstclear(&head, del);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*head;
	void	*content;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	head = NULL;
	while (lst != NULL)
	{
		content = f(lst->content);
		new = ft_lstnew(content);
		if (new == NULL)
			return (ft_free_lst(head, del, content), NULL);
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}
