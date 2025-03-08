/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
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

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = nb * (-1);
	}
	if (nb >= 10)
	{
		ft_putnbr_fd((nb / 10), fd);
		ft_putnbr_fd((nb % 10), fd);
	}
	else
		ft_putchar_fd(nb + 48, fd);
}
/*
void	ft_putnbr_fd(int n, int fd)
{
    long int	nb;

    nb = n;
    if (nb < 0)
    {
        ft_putchar_fd('-', fd);
        nb = -nb;
    }
    if (nb >= 10)
    {
        ft_putnbr_fd(nb / 10, fd);
    }
    ft_putchar_fd((nb % 10) + 48, fd);
}
======== TEST MAIN=====
int	main(void)
{
    // Test writing to standard output (stdout)
    ft_putnbr_fd(123, 1);
	ft_putchar_fd('\n', 1);

    // Test writing to standard error (stderr)
    ft_putnbr_fd(123, 2);
	ft_putchar_fd('\n', 2);

    return (0);
}
*/
