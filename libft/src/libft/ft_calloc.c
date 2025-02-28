/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:12:27 by niperez           #+#    #+#             */
/*   Updated: 2024/05/26 01:03:56 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = count * size;
	ptr = NULL;
	if ((count != 0 && total_size / count == size) || count == 0)
		ptr = (void *) malloc(total_size);
	if (ptr != NULL)
		ft_bzero(ptr, total_size);
	return (ptr);
}
