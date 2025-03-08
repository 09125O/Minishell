/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* 
 get str
 * Extracts a line from the given string.
 * @str: The original string containing the data read from the file.
 * Return: A new string containing the extracted line.
*/
char	*get_str(char *data)
{
	int		len;
	char	*new_str;

	len = 0;
	if (!data[len])
		return (NULL);
	while (data[len] && data[len] != '\n')
		len++;
	new_str = ft_calloc(len + (data[len] == '\n') + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	len = 0;
	while (data[len] && data[len] != '\n')
	{
		new_str[len] = data[len];
		len++;
	}
	if (data[len] && data[len] == '\n')
		new_str[len++] = '\n';
	return (new_str);
}

/* 
 get_left_str
 * Updates the static string with leftover data after extracting a line.
 * @str: The original string containing the data read from the file.
 * Return: 
   A new string with the leftover data or NULL if there is no leftover data.
*/
char	*get_left_str(char *data)
{
	int		i;
	int		j;
	char	*dup_str;

	i = 0;
	j = 0;
	while (data[i] && data[i] != '\n')
		i++;
	if (!data[i])
	{
		free(data);
		return (NULL);
	}
	dup_str = ft_calloc((ft_strlen(data) - i + 1), sizeof(char));
	if (!dup_str)
		return (free(data), NULL);
	i += 1;
	while (data[i])
	{
		dup_str[j] = data[i];
		i++;
		j++;
	}
	free(data);
	return (dup_str);
}

/* 
 read_n_append (str by str)
 * Reads data from the file and appends it to the existing string.
 * @str: The existing string containing previously read data.
 * @fd: The file descriptor to read from.
 * Return: The updated string with the newly read data.
*/
char	*read_n_append(int fd, char *str)
{
	char	*buffer;
	int		bytes_read;

	if (!str)
		str = ft_calloc(1, 1);
	if (!str)
		return (NULL);
	bytes_read = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(str), NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(str), free(buffer), NULL);
		buffer[bytes_read] = '\0';
		str = ft_strjoin(str, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*left_data[MAX_FD];
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (left_data[fd])
		{
			free(left_data[fd]);
			left_data[fd] = NULL;
		}
		return (NULL);
	}
	left_data[fd] = read_n_append(fd, left_data[fd]);
	if (!left_data[fd])
		return (NULL);
	result = get_str(left_data[fd]);
	if (!result)
		return (free(left_data[fd]), left_data[fd] = NULL, NULL);
	left_data[fd] = get_left_str(left_data[fd]);
	return (result);
}
/*
#include <stdio.h>

int main(int ac, char *av[])
{
	char *read_line;
	int	fd;
	int i;

	if (ac < 2)
	{
		printf("ERROR! CORRECT FORMAT: %s <file1> <file2>...\n", av[0]);
	}
	i = 1;
	while (i < ac)
	{
		fd = open(av[i], O_RDONLY);
		// read_line = get_next_line(fd);
		if (fd < 0)
		{
			perror("ERROR!");
			i++;
			continue;
		}
		while ((read_line = get_next_line(fd)) != NULL)
		{
			printf("%s", read_line);
			free(read_line);
		}
		close(fd);
		i++;
	}
	return (0);
}
*/
