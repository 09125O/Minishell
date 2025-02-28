/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:19:30 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/26 20:40:17 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Vérifie si une chaîne de caractères ne contient que des chiffres
 * @param str La chaîne à vérifier
 * @return 1 si la chaîne ne contient que des chiffres, 0 sinon
 */
int	ft_isdigit_str(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);

	// Gestion du signe négatif au début
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;

	// Si la chaîne ne contient que le signe, ce n'est pas un nombre
	if (!str[i])
		return (0);

	// Vérification que tous les caractères sont des chiffres
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}

	return (1);
}
