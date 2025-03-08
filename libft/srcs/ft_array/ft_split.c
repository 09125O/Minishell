/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_all(char **arr, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(arr[i++]);
	free(arr);
}

static char	*ft_strchop(char const *s, int start, int end)
{
	char	*str;

	str = (char *)malloc((end - start) * sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, s + start + 1, end - start);
	return (str);
}

static int	ft_assign_arr(char **arr, char const *s, char c, int s_len)
{
	int	i;
	int	j;
	int	anchor;

	i = -1;
	j = 0;
	anchor = i;
	while (++i <= s_len)
	{
		if (s[i] == c || !s[i])
		{
			if (i - anchor > 1)
			{
				arr[j] = ft_strchop(s, anchor, i);
				if (!arr[j++])
				{
					ft_free_all(arr, j - 1);
					return (0);
				}
			}
			anchor = i;
		}
	}
	arr[j] = 0;
	return (1);
}

static int	ft_count_subset(char const *s, char c, int s_len)
{
	int	i;
	int	cnt;
	int	anchor;

	i = -1;
	cnt = 0;
	anchor = i;
	while (++i <= s_len)
	{
		if (s[i] == c || !s[i])
		{
			if (i - anchor > 1)
				cnt++;
			anchor = i;
		}
	}
	return (cnt);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		s_len;
	int		n_subset;

	s_len = (int)ft_strlen(s);
	n_subset = ft_count_subset(s, c, s_len);
	arr = (char **)malloc((n_subset + 1) * sizeof(char *));
	if (!arr)
		return (0);
	if (ft_assign_arr(arr, s, c, s_len) == 0)
		return (0);
	return (arr);
}
// ===MINE====
// static void	ft_free_strs(char **strs, int count)
// {
// 	int	i;

// 	i = 0;
// 	if (!strs)
// 		return;
// 	while (i < count)
// 	{
// 		free((char *)strs[i]);
// 		i++;
// 	}
// 	free((char **)strs);
// }

// static int	ft_wordcount(char const *str, char c)
// {
// 	int	wordlen;
// 	int	in_word;

// 	wordlen = 0;
// 	in_word = 0;
// 	while (*str)
// 	{
// 		if (*str != c && !in_word)
// 		{
// 			in_word = 1;
// 			wordlen++;
// 		}
// 		else if (*str == c)
// 		{
// 			in_word = 0;
// 		}
// 		str++;
// 	}
// 	return (wordlen);
// }

// static char	*ft_stralloc(char const *str, char c, int *end_pos)
// {
// 	char	*total_word;
// 	int		start_pos;
// 	int		i;

// 	i = 0;
// 	start_pos = *end_pos;
// 	while (str[start_pos] && str[start_pos] == c)
// 		start_pos++;
// 	while (str[start_pos + i] && str[start_pos + i] != c)
// 		i++;
// 	total_word = (char *)malloc((i + 1) * sizeof(char));
// 	if (!total_word)
// 		return (NULL);
// 	i = 0;
// 	while (str[start_pos] && str[start_pos] != c)
// 	{
// 		total_word[i++] = str[start_pos++];
// 	}
// 	total_word[i] = '\0';
// 	*end_pos = start_pos;
// 	return (total_word);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**sub_strs;
// 	int		i;
// 	int		pos;
// 	int		wordlen;

// 	i = 0;
// 	pos = 0;
// 	wordlen = ft_wordcount(s, c);
// 	sub_strs = (char **)malloc((wordlen + 1) * sizeof(char *));
// 	if (!sub_strs)
// 		return (NULL);
// 	while (i < wordlen)
// 	{
// 		sub_strs[i] = ft_stralloc(s, c, &pos);
// 		if (!sub_strs[i])
// 		{
// 			ft_free_strs(sub_strs, i);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	sub_strs[i] = NULL;
// 	return (sub_strs);
// }

/*OTHERS
#include <stdio.h>
int	main(int ac, char *av[])
{
	char **result;
	int	i;

	(void)ac;
	result = ft_split(av[1], av[2][0]);
	i = 0;
	while (i < ac)
	{
		printf("|| %s ||\n", result[i]);
		i++;
	}
	free(result);
	return (0);
}

#include <stdio.h>
int	main(void)
{
    char **result;
    char *test_string = "This~is~a~test~string";
    char delimiter = '~';
    int i;

    // Call your ft_split function
    result = ft_split(test_string, delimiter);

    // Check if the result is NULL (allocation failed or other error)
    if (!result)
    {
        printf("Error: ft_split returned NULL\n");
        return (1);
    }

    // Print each string in the result array
    for (i = 0; result[i] != NULL; i++)
    {
        printf("Substring %d: %s\n", i, result[i]);
    }

    // Free the allocated memory
    ft_free_strs(result, i); // Assuming ft_free_strs is corrected as suggested

    return (0);
}
*/
