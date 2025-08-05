/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:13:17 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:13:17 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* @s1: Primo blocco di memoria. @s2: Secondo blocco di memoria.
@n: Numero massimo di byte da confrontare. Restituisce: Un valore negativo 
se s1 < s2. - 0 se s1 == s2. - Un valore positivo se s1 > s2. */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ps1;
	const unsigned char	*ps2;
	size_t				i;

	ps1 = (const unsigned char *)s1;
	ps2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (ps1[i] != ps2[i])
			return ((int)(ps1[i] - ps2[i]));
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	str1[] = "Hello, World!";
	char	str2[] = "Hello, World!";
	char	str3[] = "Hello, un cavolo";

	printf("Confronto str1 e str2: %d\n", ft_memcmp(str1, str2, 13));
	printf("Confronto str1 e str3: %d\n", ft_memcmp(str1, str3, 13));
	return (0);
}*/
