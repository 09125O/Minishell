/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:24:26 by niperez           #+#    #+#             */
/*   Updated: 2024/05/25 19:31:25 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*tmp;

	if (lst != NULL && *lst != NULL && *del != NULL)
	{
		node = *lst;
		while (node != NULL)
		{
			tmp = node->next;
			ft_lstdelone(node, del);
			node = tmp;
		}
		*lst = NULL;
	}
}
