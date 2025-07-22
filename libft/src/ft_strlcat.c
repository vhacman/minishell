/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:15:35 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:15:50 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = 0;
	src_len = ft_strlen(src);
	i = 0;
	while (dest_len < destsize && dest[dest_len])
		dest_len++;
	if (destsize <= dest_len)
		return (destsize + src_len);
	while (src[i] && (dest_len + i) < (destsize - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if ((dest_len + i) < destsize)
		dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
/*
int	main(void)
{
	char	dest1[20] = "Hello, ";
	const char	*src;
       
	src	= "42 School";
	size_t	size;
	size	= 15;
	size_t	result;
       
	result = ft_strlcat(dest1, src, size);
	printf("Destinazione: \"%s\"\n", dest1);
	printf("Lunghezza finale: %zu\n", result);
	return (0);
}*/
