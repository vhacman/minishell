/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:11:13 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:11:13 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*The function sets the first `n` bytes of the memory area pointed
to by `s` to `'\0'`. It does not return anything.  
It is used to clear a memory area by setting its bytes to `0`.*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n)
	{
		*p++ = 0;
		--n;
	}
}
/*
int	main(void)
{
	char	str[10] = "Hello 42";
	char	*p;

	//str[10] = "Hello42";
	p = str;
	printf("Before ft_bzero: \"%s\"\n", str);
	ft_bzero(str, 5);
	printf("After ft_bzero: \"");
	while (*p)
	{
		printf("%c", *p);
		p++;
	}
	while (p < str + 10)
	{
		printf("\\0");
		p++;
	}
	printf("\"\n");
	return (0);
}*/
