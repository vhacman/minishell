/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:16:53 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:17:02 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurance;
	char	target;

	last_occurance = NULL;
	target = (char)c;
	while (*s)
	{
		if (*s == target)
			last_occurance = (char *)s;
		s++;
	}
	if (target == 0)
		return ((char *)s);
	return (last_occurance);
}
/*
int main(void)
{
    const char *test_string = "Hello, world!"; // Stringa di test
    char target_char;                          // Carattere da cercare
    char *result;                              // Risultato della funzione

    // Test 1: Cerca il carattere 'o'
    target_char = 'o';
    result = ft_strrchr(test_string, target_char);
    printf("Test 1:\n");
    printf("Stringa: \"%s\"\n", test_string);
    printf("Carattere da cercare: '%c'\n", target_char);
    if (result)
        printf("Ultima occorrenza trovata: \"%s\"\n\n", result);
    else
        printf("Carattere '%c' non trovato nella stringa.\n\n", target_char);

    // Test 2: Cerca un carattere non presente ('x')
    target_char = 'x';
    result = ft_strrchr(test_string, target_char);
    printf("Test 2:\n");
    printf("Stringa: \"%s\"\n", test_string);
    printf("Carattere da cercare: '%c'\n", target_char);
    if (result)
        printf("Ultima occorrenza trovata: \"%s\"\n\n", result);
    else
        printf("Carattere '%c' non trovato nella stringa.\n\n", target_char);

    // Test 3: Cerca il terminatore '\0'
    target_char = '\0';
    result = ft_strrchr(test_string, target_char);
    printf("Test 3:\n");
    printf("Stringa: \"%s\"\n", test_string);
    printf("Carattere da cercare: '\\0'\n");
    if (result)
        printf("Ultima occorrenza di '\\0': puntatore a \"%s\"\n\n", result);
    else
        printf("Carattere '\\0' non trovato nella stringa.\n\n");

    return 0;
}*/
