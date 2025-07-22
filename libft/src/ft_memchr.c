/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:12:52 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:12:52 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*Searches for the first occurrence of a specific byte (c) in a memory block
(s) with a maximum length (n). Returns a pointer to the first matching byte
or NULL if the byte is not found. The search is performed byte by byte
and uses a cast to unsigned char to ensure correctness.*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned int		i;

	if (s == NULL)
		return (NULL);
	ptr = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)(ptr + i));
		i++;
	}
	return (NULL);
}
/*
int	 main(void)
{
    char	str[] = "Hello, World!";
    char	*result = ft_memchr(str, 'W', 13); // Cerca 'W' nei primi 13 byte
    if (result != NULL)
        printf("Carattere trovato: %s\n", result);
    else
        printf("Carattere non trovato!\n");

    return 0;
}*/
