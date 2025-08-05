/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:15:02 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/31 12:44:33 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}
/*
int	main(void)
{
	const char	str[] = "Hello, 42!";
	char		c;
	char		*result;

	c = 'o';
	printf("Original string: \"%s\"\n", str);
	printf("Character to find: '%c'\n", c);
	result = ft_strchr(str, c);
	if (result)
		printf("Character found at position: %ld\n", result - str);
	else
		printf("Character not found in the string.\n");
	return (0);
}*/
/*
int main(void)
{
    const char str[] = "Hello, 42!";
    char c;
    char *result;

    c = 'o';
    printf("Original string: \"%s\"\n", str);
    printf("Character to find: '%c'\n", c);
    result = ft_strchr(str, c);
    if (result)
        printf("Character found at position: %ld\n", result - str);
    else
        printf("Character not found in the string.\n");
    c = 'H';
    printf("\nOriginal string: \"%s\"\n", str);
    printf("Character to find: '%c'\n", c);
    result = ft_strchr(str, c);
    if (result)
        printf("Character found at position: %ld\n", result - str);
    else
        printf("Character not found in the string.\n");
    c = '!';
    printf("\nOriginal string: \"%s\"\n", str);
    printf("Character to find: '%c'\n", c);
    result = ft_strchr(str, c);
    if (result)
        printf("Character found at position: %ld\n", result - str);
    else
        printf("Character not found in the string.\n");
    c = 'x';
    printf("\nOriginal string: \"%s\"\n", str);
    printf("Character to find: '%c'\n", c);
    result = ft_strchr(str, c);
    if (result)
        printf("Character found at position: %ld\n", result - str);
    else
        printf("Character not found in the string.\n");
    const char empty_str[] = "";
    c = 'a';
    printf("\nOriginal string: \"%s\"\n", empty_str);
    printf("Character to find: '%c'\n", c);
    result = ft_strchr(empty_str, c);
    if (result)
        printf("Character found at position: %ld\n", result - empty_str);
    else
        printf("Character not found in the string.\n");
    c = '\0';
    printf("\nOriginal string: \"%s\"\n", str);
    printf("Character to find: '%c' (null terminator)\n", c);
    result = ft_strchr(str, c);
    if (result)
        printf("Character found at position: %ld\n", result - str);
    else
        printf("Character not found in the string.\n");

    return (0);
}*/
