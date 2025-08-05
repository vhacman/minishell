/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:59:03 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/10 16:30:09 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count = count + write(1, "-2147483648", 11);
		return (count);
	}
	if (n < 0)
	{
		count = count + ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		count = count + ft_putnbr(n / 10);
	count = count + ft_putchar(n % 10 + '0');
	return (count);
}

/*
int	main(void)
{
	// Test di numeri positivi
	ft_putnbr(42);
	ft_putchar('\n');
	ft_putnbr(12345);
	ft_putchar('\n');

	// Test di numeri negativi
	ft_putnbr(-7);
	ft_putchar('\n');
	ft_putnbr(-98765);
	ft_putchar('\n');

	// Test del caso limite (minimo valore di un int)
	ft_putnbr(-2147483648);
	ft_putchar('\n');

	// Test del massimo valore di un int
	ft_putnbr(2147483647);
	ft_putchar('\n');

	return (0);
}*/