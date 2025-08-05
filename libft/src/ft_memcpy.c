/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:13:34 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:13:34 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*The function copies exactly `n` bytes from the source memory `src` to the
destination memory `dest`. It does not handle overlapping memory areas,
unlike `memmove`.It returns a pointer to the destination memory `dest`.  
It does not automatically copy the null terminator; 
it is the user's responsibility to manage such data if required.*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	src[] = "Hello, World!";
	char	dest[20];

	printf("Before ft_memcpy: %s\n", dest);
	ft_memcpy(dest, src, ft_strlen(src) + 1);
	printf("After ft_memcpy: %s\n", dest);
	return (0);
}*/
