/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:05:51 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/10 16:05:51 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *La funzione `ft_putptr` stampa un indirizzo di memoria sotto 
 *forma di stringa esadecimale,  *prefissata dal simbolo "0x". 
 *Se l'indirizzo passato è NULL, stampa la stringa "(nil)".
 *Altrimenti, converte l'indirizzo in esadecimale e lo stampa. 
 *La funzione restituisce il numero totale di caratteri stampati,
 *inclusi "0x" e l'indirizzo esadecimale.
 */
int	ft_putptr(void *ptr)
{
	unsigned long	p;
	int				count;

	count = 0;
	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	p = (unsigned long)ptr;
	write(1, "0x", 2);
	count += 2;
	count += ft_putnbr_hex(p, 0);
	return (count);
}
