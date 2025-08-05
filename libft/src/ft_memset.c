/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:18:48 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 20:18:48 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*The function is used to fill a memory area with a specified value,
byte by byte. The function takes the following inputs:A pointer (`b`) to
the memory area to be modified; A value (`c`), converted to `unsigned char`,
to be copied into each byte; A count (`count`), representing the
number of bytes to fill. Operations performed:Converts `b` to a `char*`
pointer to access individual bytes;Iterates for `count` bytes,
setting each byte to the value `c`; Returns the original pointer `b`.  
Special cases:If `count == 0`, it does not modify anything but still returns `b`
- If `b == NULL`, the behavior is undefined.*/
#include "libft.h"

void	*ft_memset(void *b, int c, size_t count)
{
	size_t	cur;
	char	*data;

	cur = 0;
	data = (char *)b;
	while (cur < count)
	{
		data[cur] = c;
		cur++;
	}
	return (b);
}
/*
int	main(void)
{
	char	str[10] = "Hello!";
	printf("Before ft_memset: %s\n", str);
	ft_memset(str, '*', 3);
	printf("After ft_memset: %s\n", str);
	return (0);
}*/