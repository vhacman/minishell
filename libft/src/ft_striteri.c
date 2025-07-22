/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:34:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/30 23:34:20 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ft_striteri takes a string s and a function f. It applies f to each character
of the string, passing the index of the character as the first argument and a 
pointer to the character (so it can be modified if needed)as the second arg.
The index is used as the first argument to f.The character is passed by 
reference (i.e., its address) as the second argument, allowing f to modify 
the character if necessary.*/

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = -1;
	while (s[++i])
		f(i, &s[i]);
}
