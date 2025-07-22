/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:14:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:14:20 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*writes an int to a specified file descriptor. This type of function is useful 
when you want to output a number to a file or other output devices
(like a screen or network),without necessarily using printf or other standard 
library functions*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	write (fd, &c, 1);
}
/*
int     main(void)
{
    int number = -12345;
    ft_putnbr_fd(number, 1);
    write(1, "\n", 1);
    return (0);
}*/
