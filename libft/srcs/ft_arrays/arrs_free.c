/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrs_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** @note
 * - Loop to free each array
 * - Free pointer itself in the end
 */
void	arrs_free(char **arrs)
{
	int	i;

	i = 0;
	while (arrs[i])
	{
		free(arrs[i]);
		i++;
	}
	free(arrs);
}
