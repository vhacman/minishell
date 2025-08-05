/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:13:43 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:13:43 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*Used to copy a block of memory from one location to another. It is designed
to safely copy a sequence of bytes from `src` to `dest`, even when the memory
areas overlap. When the areas overlap and `dest > src`,
the function copies the data starting  from the end of the src area to the
end of the destination area.*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char			*d;
	const unsigned char		*s;
	unsigned char			i;

	if (!dest && !src)
		return (NULL);
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	if (d > s)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	char	str1[] = "Hello, World!";
	char	overlap_dest[] = "OverlapTest";

	// Caso 1: Nessuna sovrapposizione
	printf("Caso 1: Nessuna sovrapposizione\n");
	printf("Prima di ft_memmove: str1 = \"%s\"\n", str1);
	ft_memmove(str1 + 7, str1, 5);
	printf("Dopo ft_memmove: str1 = \"%s\"\n", str1);
	
	// Caso 2: Sovrapposizione (da destra a sinistra)
	printf("\nCaso 2: Sovrapposizione (da destra a sinistra)\n");
	printf("Prima di ft_memmove: overlap_dest = \"%s\"\n", overlap_dest);
	ft_memmove(overlap_dest + 3, overlap_dest, 7);
	printf("Dopo ft_memmove: overlap_dest = \"%s\"\n", overlap_dest);
	return (0);
}*/
