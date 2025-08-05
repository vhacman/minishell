/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:15:23 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:15:23 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*This function duplicates a string, verifying the source, allocating memory, 
copying the content, and returning a pointer to the new string. 
If memory allocation fails or the source is null, it returns NULL. 
Called “ft_strdup,” it uses ft_strlen and ft_strcpy.*/
#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (len + 1 == 0)
		return (NULL);
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	ft_strcpy(s2, s1);
	return (s2);
}
/*
int	main(void)
{
    // Caso 1: Stringa normale
    char	str1[] = "42 Network";
    char	*copy1 = ft_strdup(str1);
    printf("Originale: %s | Copia: %s\n", str1, copy1);
    free(copy1);

    // Caso 2: Stringa vuota
    char	str2[] = "";
    char	*copy2 = ft_strdup(str2);
    printf("Stringa vuota: '%s'\n", copy2);
    free(copy2);

    // Caso 3: NULL (deve restituire NULL)
    char	*copy3 = ft_strdup(NULL);
    printf("NULL: %p\n", (void *)copy3);

    return (0);
}*/
