/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:15:59 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:15:59 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}
/*
int	main(void)
{
	char	src[] = "Hello, World!";
	char	dest[20]; // Buffer grande abbastanza
	char	 small_dest[5]; // Buffer piccolo
	size_t	result;

	// Test con buffer grande
	result = ft_strlcpy(dest, src, sizeof(dest));
	printf("Buffer grande: %s (lunghezza attesa: %zu)\n", dest, result);

	// Test con buffer piccolo
	result = ft_strlcpy(small_dest, src, sizeof(small_dest));
	printf("Buffer piccolo: %s (lunghezza attesa: %zu)\n", small_dest, result);

	return (0);
}*/
