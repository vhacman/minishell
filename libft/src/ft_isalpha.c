/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:11:39 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/31 00:37:30 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
/*
int	main(void)
{
	char	test_chars[] = {'A', 'z', '1', '%', '9', ' ', 'B'};
	int	i = 0;

	while (test_chars[i])
 	{
		if (ft_isalpha(test_chars[i]))
 			printf("'%c' is alpha.\n", test_chars[i]);
		else
			printf("'%c' is NOT alpha\n", test_chars[i]);
				i++;
	}
	return 0;
}*/
