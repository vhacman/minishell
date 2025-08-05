/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:14:49 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:14:49 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
/*
int	main(void)
{
	// Test su stdout (file descriptor 1)
	ft_putstr_fd("Hello, World!\n", STDOUT_FILENO);

	// Test su stderr (file descriptor 2)
	ft_putstr_fd("Errore di test!\n", STDERR_FILENO);

	// Test con stringa vuota
	ft_putstr_fd("", STDOUT_FILENO);

	// Test con NULL (non deve stampare nulla e non deve crashare)
	ft_putstr_fd(NULL, STDOUT_FILENO);

	return (0);
}*/
