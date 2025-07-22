/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:09:48 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/10 16:09:48 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_hex(unsigned long n, int upper)
{
	char	*hex_digits;
	int		count;

	count = 0;
	if (upper)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	if (n >= 16)
		count += ft_putnbr_hex (n / 16, upper);
	count += ft_putchar(hex_digits[n % 16]);
	return (count);
}
