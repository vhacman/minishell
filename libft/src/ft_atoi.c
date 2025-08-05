/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:10:31 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/10 11:41:41 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*	Questa funzione serve per gestire gli spazi iniziali e il segno (+ o -) 
all'inizio della stringa prima di passare alla conversione del 
numero vero e proprio.*/
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

static int	ft_calculate_number(const char *str, int *i, int sign)
{
	int	result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		if (result > (INT_MAX - (str[*i] - '0') / 10))
		{
			if (sign == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		result = result * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = ft_handle_sign_and_spaces(str, &i);
	result = ft_calculate_number(str, &i, sign);
	return (result * sign);
}
/*
int	main(void)
{
    printf("Test 1: %d\n", ft_atoi("42"));          
    printf("Test 2: %d\n", ft_atoi("-42"));         
    printf("Test 3: %d\n", ft_atoi("+42"));       
    printf("Test 4: %d\n", ft_atoi("   42"));       
    printf("Test 5: %d\n", ft_atoi("   -42"));      
    printf("Test 6: %d\n", ft_atoi("  +42"));       
    printf("Test 7: %d\n", ft_atoi("42abc"));       
    printf("Test 8: %d\n", ft_atoi("abc42"));       
    printf("Test 9: %d\n", ft_atoi("2147483647"));   
    printf("Test 10: %d\n", ft_atoi("-2147483648")); 
    printf("Test 11: %d\n", ft_atoi("2147483648"));  
    printf("Test 12: %d\n", ft_atoi("-2147483649"));
    printf("Test 13: %d\n", ft_atoi("   +42abc"));   
    printf("Test 14: %d\n", ft_atoi("   -42abc"));   
    printf("Test 15: %d\n", ft_atoi("42    abc"));   
    printf("Test 16: %d\n", ft_atoi("   +2147483647"));  
    printf("Test 17: %d\n", ft_atoi("   -2147483648")); 
    printf("Test 18: %d\n", ft_atoi(""));           
    printf("Test 19: %d\n", ft_atoi("   "));        
    return 0;
}*/
