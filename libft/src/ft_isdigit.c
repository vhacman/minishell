/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:10:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/31 00:38:18 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
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
		if (ft_isdigit(test_chars[i]))
 			printf("'%c' is digit.\n", test_chars[i]);
		else
			printf("'%c' is NOT digit.\n", test_chars[i]);
				i++;
	}
	return 0;
}*/
