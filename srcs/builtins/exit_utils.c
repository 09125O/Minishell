/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/09 00:14:01 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"
#include <ctype.h>

/** CHECK_OVERFLOW
 * @param long boundary;
 * // Store the limit for the overflow check
 * @param long digit_value = digit - '0';
 * // Convert char to int value
 * (1) Determine the boundary depending on the sign
 * (positive or negative)
 * (2) For positive numbers, use LONG_MAX
 * -> Check for overflow for positive numbers
 * (3) For negative numbers, use LONG_MIN
 * -> Check for overflow for negative numbers
 * @return (1) overflow detected / (0) no overflow
 */
static int	check_overflow(long res, int sign, char digit)
{
	long	boundary;
	long	digit_value;

	digit_value = digit - '0';
	if (sign == 1)
	{
		boundary = LONG_MAX / 10;
		if (res > boundary || (res == boundary && digit_value > LONG_MAX % 10))
			return (1);
	}
	else
	{
		boundary = -(LONG_MIN / 10);
		if (res > boundary || (res == boundary && digit_value > -(LONG_MIN
					% 10)))
			return (1);
	}
	return (0);
}

/** FT_ATOL / CHECK OVERFLOW
 * @param long boundary;
 * // Store the limit for the overflow check
 * @param long digit_value = digit - '0';
 * // Convert char to int value
 * (1) Determine the boundary depending on the sign
 * (positive or negative)
 * (2) For positive numbers, use LONG_MAX
 * -> Check for overflow for positive numbers
 * (3) For negative numbers, use LONG_MIN
 * -> Check for overflow for negative numbers
 * @return (1) overflow detected / (0) no overflow
 */
int	ft_atol_overflow(const char *str, long *result)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		else
			sign = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (check_overflow(res, sign, *str) == 1)
			return (1);
		res = res * 10 + (*str - '0');
		str++;
	}
	*result = res * sign;
	return (0);
}

/** CHECK_EXIT_CODE
 * @param *char tmp : point to the provided value
 * -> Preserving the Original Pointer
 * (1) If the value starts with '+' or '-' -> skip the sign
 * (2) Iterate through each character in the value to check if it's a digit
 * (3) Convert the value to a long integer with ft_atol()
 * (4) Check if the number overflows OR underflows the range of valid exit_code
 * @note 2-step casting!!
 * exit_status = (unsigned char *)exit_nb;
 * -> Ensures ft_exit.c: Errorthe value is constrained to 8 bits (0–255).
 * (long)exit_status != exit_nb;
 * -> Compare the modified value with og value to detect discrepancies.
 * @return (0) if is a valid exit code
 */
int	check_exitcode(char *input_line)
{
	char	*tmp;

	tmp = input_line;
	if (!input_line || !*input_line)
		return (1);
	while (*tmp == ' ' || (*tmp >= 9 && *tmp <= 13))
		tmp++;
	if (*tmp == '\0')
		return (1);
	if ((*tmp == '+' || *tmp == '-') && *(tmp + 1))
		tmp++;
	while (*tmp)
	{
		if (!isdigit(*tmp))
			return (1);
		tmp++;
	}
	return (0);
}
