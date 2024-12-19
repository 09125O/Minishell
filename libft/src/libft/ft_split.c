/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:30:31 by niperez           #+#    #+#             */
/*   Updated: 2024/08/26 19:13:59 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *str, char c)
{
	size_t	i;
	int		cpt;

	i = 0;
	cpt = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			cpt++;
		i++;
	}
	return (cpt);
}

static size_t	word_len(char const *str, size_t k, char c)
{
	size_t	i;

	i = 0;
	while (str[k + i] != c && str[k + i] != '\0')
		i++;
	return (i);
}

static void	ft_free_tab(char **tab, size_t index)
{
	while (index)
		free(tab[--index]);
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**tab;

	tab = (char **) malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	tab[ft_count_words(s, c)] = 0;
	k = 0;
	i = 0;
	while (i < ft_count_words(s, c))
	{
		while (s[k] == c)
			k++;
		tab[i] = (char *) malloc(sizeof(char) * (word_len(s, k, c) + 1));
		if (tab[i] == NULL)
			return (ft_free_tab(tab, i), NULL);
		tab[i][word_len(s, k, c)] = '\0';
		j = 0;
		while (word_len(s, k, c) > 0)
			tab[i][j++] = s[k++];
		i++;
	}
	return (tab);
}
