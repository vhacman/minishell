/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:59:39 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/10 15:59:40 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The ft_strcmp function compares two strings character by character.
It returns the difference between the ASCII values 
of the first differing characters.
The function is robust and efficient but requires both strings 
to be properly null-terminated (\0) to avoid undefined behavior.*/

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] == s2[i]) && (s1[i] != '\0') && (s2[i] != '\0'))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
int	main(void)
{
	const char	*str1 = "Hello";
	const char	*str2 = "Hello";
	const char	*str3 = "Hell";
	const char	*str4 = "Helloo";
	const char	*str5 = "Hi";
	printf("Test 1: Confronto tra \"%s\" e \"%s\": %d\n", 
	str1, str2, ft_strcmp(str1, str2));
	printf("Test 2: Confronto tra \"%s\" e \"%s\": %d\n",
       	str3, str1, ft_strcmp(str3, str1));
	printf("Test 3: Confronto tra \"%s\" e \"%s\": %d\n",
       	str4, str1, ft_strcmp(str4, str1));
	printf("Test 4: Confronto tra \"%s\" e \"%s\": %d\n",
       	str1, str5, ft_strcmp(str1, str5));
	printf("Test 5: Confronto tra \"%s\" e \"\": %d\n",
       	str1, ft_strcmp(str1, ""));
	return (0);
}*/
