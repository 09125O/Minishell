/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void ft_putstr_fd(char *s, int fd)
{
	write(fd, s, strlen(s));
}
*/
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
/*
int	main(void)
{
    // Test writing to standard output (stdout)
    ft_putendl_fd("AAA", 1);

    // Test writing to standard error (stderr)
    ft_putendl_fd("ERROR", 2);

    return (0);
}*/