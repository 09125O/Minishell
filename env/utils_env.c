/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:52:00 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/17 12:39:59 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void free_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size_vars)
	{
		free(env->vars[i]);
		i++;
	}
	free(env->vars);
	free(env);
}

void	errors_env(void)
{
	perror(ERROR_ENV_MESS);
	exit(EXIT_FAILURE); // Gerer potentiellement le "$?"
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
