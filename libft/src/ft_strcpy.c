/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:59:48 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/10 15:59:49 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The `strcpy` function copies a source string into a destination,
including the null terminator (`\0`).
It requires the destination to have sufficient space.
This function is useful when working with preallocated
buffers and the sizes involved are known.*/
#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int	main(void)
{
	const char	src[] = "Hello, 42!";
	char		dest[20];
	printf("Stringa originale (src): \"%s\"\n", src);
	ft_strcpy(dest, src);
	printf("Stringa copiata(dest): \"%s\"\n", dest);
	return (0);
}*/
