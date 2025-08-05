/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:29:41 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 23:29:41 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The function ft_calloc allocates memory for number elements, each of size
bytes, and initializes the memory to zero.If the memory allocation succeeds, 
it uses ft_bzero to set all the bytes of the allocated memory to zero.
If allocation fails, it returns NULL.
It returns a pointer to the newly allocated memory,
which is initialized to zero.*/

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = count * size;
	if (count != 0 && total_size / count != size)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
