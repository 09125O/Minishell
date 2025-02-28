/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:57:37 by niperez           #+#    #+#             */
/*   Updated: 2024/07/26 17:57:30 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int		ft_printf(const char *format, ...);
void	print_char(char c, int *count);
void	print_str(char *str, int *count);
void	print_pointer(unsigned long long ptr, int *count);
void	print_integer(int n, int *count);
void	print_unsigned_int(unsigned int n, int *count);
void	print_hex(unsigned int n, int is_upper_case, int *count);
void	print_number(unsigned long long n, char *base, size_t size, int *count);

#endif
