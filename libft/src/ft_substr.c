/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:09:57 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/31 14:12:50 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*Used to extract a substring from a given string.
s: The string from which the substring will be created.
start: The starting index of the substring.
len: The maximum length of the substring.*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	copy_len;
	size_t	str_len;
	size_t	i;
	char	*sub_str;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (start + len > str_len)
		copy_len = str_len - start;
	else
		copy_len = len;
	sub_str = (char *)malloc(copy_len + 1);
	if (!sub_str)
		return (NULL);
	i = 0;
	while (i < copy_len)
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}
/*
int     main(void)
{
        const char  *str = "Hello, World!";
        char        *sub = ft_substr(str, 7, 5);

        if (sub)
        {
                printf("Substring: %s\n", sub);
                free(sub);
        }
        else
                printf("Memory allocation failed\n");
        return (0);
}*/
