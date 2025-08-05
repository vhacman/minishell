/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:59:28 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/10 15:59:29 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The `ft_strcat` function concatenates two strings by copying the
characters of `s2` to the end of `s1`. It requires `s1` to have
enough allocated space to hold both strings and `s2` to be
a valid null-terminated string (`\0`). The concatenation is performed 
character by character, and a new null terminator is added at the end.*/

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int	i;

	i = ft_strlen(s1);
	while (*s2 != '\0')
	{
		s1[i] = *s2;
		i++;
		s2++;
	}
	s1[i] = '\0';
	return (s1);
}
/*
int	main(void)
{
	char str1[20] = "Hello, ";  // Deve avere spazio extra!
	char str2[] = "World!";

	printf("Prima: %s\n", str1);
	ft_strcat(str1, str2);
	printf("Dopo: %s\n", str1);

	return (0);
}*/
