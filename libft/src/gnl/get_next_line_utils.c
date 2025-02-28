/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:27:17 by niperez           #+#    #+#             */
/*   Updated: 2024/07/26 17:55:32 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_new_line(char *str)
{
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

void	free_stash(char **stash)
{
	free(*stash);
	*stash = NULL;
}

size_t	ft_len_line(char *stash)
{
	size_t	len_l;

	len_l = 0;
	while ((stash)[len_l] != '\0' && (stash)[len_l] != '\n')
		len_l++;
	if ((stash)[len_l] == '\n')
		len_l++;
	return (len_l);
}
