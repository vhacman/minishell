/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:12:35 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:12:35 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*calcola la lunghezza necessaria per rappresentare un numero n in una data
base. */
static int	ft_length(int n, int base)
{
	int	count;

	count = 0;
	if (n <= 0)
		++count;
	while (n && ++count)
		n /= base;
	return (count);
}

/*converte un numero intero in una stringa (char *)
La funzione ft_itoa lavora in base 10, il che 
significa che ogni cifra del numero può essere estratta con l'operazione 
di modulo (% 10).La funzione utilizza malloc per allocare la memoria 
necessaria per contenere la stringa, per sapere quanta memoria 
e' necessaria si usa ft_length. Il numero viene convertito dalla 
cifra meno significativa alla più significativa.
Poiché le stringhe in C sono memorizzate da sinistra a destra, l’array
viene riempito da destra a sinistra.
*/
char	*ft_itoa(int nb)
{
	int			len;
	char		*str;
	const char	*digits = "0123456789";

	len = ft_length(nb, 10);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = 0;
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
		str[0] = '-';
	while (nb)
	{
		if (nb > 0)
			str[--len] = digits[nb % 10];
		else
			str[--len] = digits[nb % 10 * -1];
		nb /= 10;
	}
	return (str);
}
/*
int     main(void)
{
	int test[] = {0, -123, 456, -2147483648, 2147483647};
	int i = 0;
	
	while (i < 5)
	{
		char *str = ft_itoa(test[i]);
		printf("ft_itoa(%d) = %s\n", test[i], str);
		free(str);
		i++;
	}
	return (0);
}*/
