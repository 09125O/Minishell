/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/09 00:22:01 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/** PRINT_EXPORT_ALL
 * Print each environment variable in the format: export NAME="VALUE"
 */
void	print_export_all(char **sorted)
{
	int		i;
	char	*tmp_value;
	char	*tmp_id;

	i = -1;
	while (sorted[++i])
	{
		printf("export ");
		tmp_value = ft_strchr(sorted[i], '=');
		if (!tmp_value)
			printf("%s\n", sorted[i]);
		else
		{
			tmp_value += 1;
			tmp_id = get_env_id(sorted[i]);
			printf("%s=\"%s\"\n", tmp_id, tmp_value);
			free(tmp_id);
		}
	}
}

/** FT_SWAP_PTR
 * Swap two string pointers
 */
static void	ft_swap_ptr(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/** SORT_ENV_ARRS
 * (1) Count the len of arrs
 * (2) copy env_arrs to reuslt, ft_strdup unsorted arrs
 * (3) sort arrs
 */
char	**sort_env_arrs(char **env_arrs)
{
	char	**result;
	int		i;
	int		j;

	result = ft_arrsdup(env_arrs);
	if (!result)
		return (arrs_free(result), NULL);
	i = -1;
	while (result[++i])
	{
		j = i + 1;
		while (result[j])
		{
			if (ft_strcmp(result[i], result[j]) > 0)
				ft_swap_ptr(&result[i], &result[j]);
			j++;
		}
	}
	return (result);
}
