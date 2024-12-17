/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:53:41 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/17 12:56:44 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*search_env_variable(t_env *env, char *key)
{
	int i;
	int	key_len;

	i = 0;
	if (!key || !env)
		return (NULL);
	key_len = ft_strlen(key);
}
