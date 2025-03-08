/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size && (nmemb / size * size) != nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
/*
void	*ft_calloc(size_t count, size_t size)
{
	void	*bloc;

	if (count == 0 || size == 0)
	{
		bloc = malloc(0);
		if (!bloc)
			return (NULL);
		return (bloc);
	}
	if ((unsigned)count != count || (unsigned)size != size)
		return (NULL);
	bloc = malloc(count * size);
	if (bloc)
		ft_bzero(bloc, count * size);
	return (bloc);
}*/