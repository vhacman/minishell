/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:50:04 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 23:50:04 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*the function checks that both string s and the function f are valid
It allocates the memory for the new string. 
It applies the function f to each character of the string s, including the
index of the charachter. It returns the new string or NULL if there was
memory allocation failure.*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	char				*str;

	if (!s && !f)
		return (NULL);
	str = (char *)malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
// Main function that simply calls ft_strmapi with ft_tolower
int     main(void)
{
    char        *str = "Hello WORLD!";
    char        *new_str = ft_strmapi(str, ft_tolower);

    if (new_str)
    {
        printf("Original string: %s\n", str);
        printf("New string: %s\n", new_str);
        free(new_str);
    }
    else
    {
        printf("Memory allocation failed.\n");
    }

    return (0);*/
