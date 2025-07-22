/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:59:13 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/10 16:28:41 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*The function prints a string (`char *s`) to the standard output,
 character by character.It accepts a pointer to a null-terminated string (`\0`). 
Before proceeding, it ensures the pointer is not `NULL`
to avoid undefined behavior; if it is, the function does nothing.
An integer variable `i` is initialized to 0 to serve as an index for accessing
the characters of the string. A `while` loop is used to iterate through 
the string, and it stops when the null terminator is encountered.*/
int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (ft_putstr("(null)"));
	while (str[count])
	{
		ft_putchar(str[count]);
		count++;
	}
	return (count);
}
/*
int	main(void)
{
	char	str1[] = "Hello, 42!";
	char	str2[] = ""; // Stringa vuota
	char	*str3 = NULL; // Puntatore nullo
	write(1, "Test 1: ", 8);
	ft_putstr(str1);
	write(1, "\n", 1);
	write(1, "Test 2: ", 8);
	ft_putstr(str2);
	write(1, "\n", 1);
	write(1, "Test 3: ", 8);
	ft_putstr(str3);
	write(1, "\n", 1);
	return (0);
}*/
