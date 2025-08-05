/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:10:31 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/29 14:15:11 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Gestisce eventuali spazi bianchi iniziali e identifica il segno (+/-)
	della stringa da convertire. Restituisce 1 o -1 a seconda del segno. */
static int	ft_handle_sign_and_spaces(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign *= -1;
		(*i)++;
	}
	return (sign);
}

/*	Calcola il valore numerico a partire dalla posizione corrente
	della stringa, tenendo conto del segno. */
static long	ft_calculate_number(const char *str, int *i)
{
	long	result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

/*	Converte la stringa `str` in un valore long, gestendo spazi,
	segni e cifre numeriche. */
long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = ft_handle_sign_and_spaces(str, &i);
	result = ft_calculate_number(str, &i);
	return (result * sign);
}
