/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:14:06 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:14:06 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int	main(void)
{
    ft_putchar_fd('A', 1);
    ft_putchar_fd('\n', 1); // Forza nuova riga

    ft_putchar_fd('E', 2);
    ft_putchar_fd('\n', 2); // Forza nuova riga per stderr
    return 0;
}*/
