/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 21:21:18 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 21:21:18 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	new_str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s1 && !s2)
		return (NULL);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		new_str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		new_str[j++] = s2[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
/*
int	main(void)
{
	char	*s1;
	char	*s2;
	char	*result;

	s1 = "Hello, ";
	s2 = "World!";
	result = ft_strjoin(s1, s2);
	if (result)
	{
		printf("%s\n", result);
		free(result);
	}
	return (0);
}*/
