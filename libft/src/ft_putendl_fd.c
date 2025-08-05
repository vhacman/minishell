/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:14:14 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:14:14 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
/*
int     main(void)
{
        ft_putendl_fd("Ciao!", STDOUT_FILENO);
	ft_putendl_fd("Questa è una riga di testo.", STDOUT_FILENO);
	ft_putendl_fd(NULL, STDOUT_FILENO); 
	return (0);
}*/
