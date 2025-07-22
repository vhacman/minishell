/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:07:02 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/10 16:07:02 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*the function returns an int representing the number of charachters printed.
If n is >= it means that has more tha 1 digit. The function calls itself
recursively (n / 10) to print the digit left.
The function than extracts the last digit of n (n % 10) and converts
to its corrisponding ASCII character (+ '0')

This function correctly prints unsigned integers and counts the number 
of characters printed. It efficiently processes multi-digit numbers using 
recursion, ensuring they are printed in the correct order.*/
#include "libft.h"

int	ft_putnbr_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count = count + ft_putnbr_unsigned(n / 10);
	count = count + ft_putchar(n % 10 + '0');
	return (count);
}
