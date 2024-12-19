/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:27:11 by niperez           #+#    #+#             */
/*   Updated: 2024/06/02 21:25:36 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_stash(char **stash)
{
	size_t	len_l;
	size_t	len_r;
	char	*tmp;
	size_t	i;

	len_l = ft_len_line(*stash);
	len_r = 0;
	while ((*stash)[len_l + len_r] != '\0')
		len_r++;
	tmp = (char *) malloc(sizeof(char) * (len_r + 1));
	if (tmp == NULL)
		return (free_stash(stash));
	i = 0;
	while (i < len_r)
	{
		tmp[i] = (*stash)[len_l + i];
		i++;
	}
	tmp[len_r] = '\0';
	free(*stash);
	*stash = tmp;
}

void	extract_line(char *str, char **line)
{
	size_t	len;
	size_t	i;

	len = ft_len_line(str);
	*line = (char *) malloc(sizeof(char) * (len + 1));
	if (*line == NULL)
		return ;
	i = 0;
	while (i < len)
		(*line)[i++] = *str++;
	(*line)[len] = '\0';
}

void	add_to(char **stash, char *buf)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*tmp;

	len1 = ft_strlen(*stash);
	len2 = ft_strlen(buf);
	tmp = *stash;
	*stash = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!*stash)
		return (free(tmp));
	i = 0;
	while (i < len1)
	{
		(*stash)[i] = tmp[i];
		i++;
	}
	free(tmp);
	i = 0;
	while (i < len2)
	{
		(*stash)[len1 + i] = buf[i];
		i++;
	}
	(*stash)[len1 + len2] = '\0';
}

void	read_and_stash(int fd, char **stash, int *nbyte)
{
	char	*buf;

	while (!found_new_line(*stash) && *nbyte > 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
		{
			if (*stash != NULL)
				free_stash(stash);
			return ;
		}
		*nbyte = read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && *nbyte == 0) || *nbyte == -1)
		{
			free(buf);
			return ;
		}
		buf[*nbyte] = '\0';
		add_to(stash, buf);
		free(buf);
	}
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	int			nbyte;

	nbyte = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_stash(fd, &stash, &nbyte);
	if (nbyte < 0)
		return (free_stash(&stash), NULL);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	if (line == NULL)
		return (free_stash(&stash), NULL);
	clean_stash(&stash);
	if (stash == NULL)
		return (free(line), NULL);
	if (line[0] == '\0')
		return (free(line), free_stash(&stash), NULL);
	return (line);
}
