/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:30:35 by mkakizak          #+#    #+#             */
/*   Updated: 2024/10/06 12:39:05 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursive_print( int num, int *res)
{
	char	print;

	if (num >= 10)
	{
		recursive_print (num / 10, res);
		print = num % 10 + '0';
		if (write(1, &print, 1) == 1)
			*res += 1;
		else
		{
			*res = -1;
			return ;
		}
	}
	else if (num < 10)
	{
		print = num % 10 + '0';
		if (write(1, &print, 1) == 1)
			*res += 1;
		else
		{
			*res = -1;
			return ;
		}
	}
}

static void	check_sign(int *n, int *res)
{
	if (write(1, "-", 1) == 1)
	{
		*n = *n * -1;
		*res += 1;
		recursive_print(*n, res);
	}
	else
		*res = -1;
}

static void	print_min(int *res)
{
	int		i;
	char	*int_min;

	int_min = "-2147483648";
	i = 0;
	while (int_min[i])
	{
		if (write(1, &int_min[i], 1) == 1)
			*res += 1;
		else
		{
			*res = -1;
			return ;
		}
		i++;
	}
}

int	ft_putnbr(int n)
{
	int	res;

	res = 0;
	if (n < 0)
	{
		if (n > INT_MIN)
			check_sign(&n, &res);
		else if (n == -2147483648)
		{
			print_min(&res);
		}
	}
	else
		recursive_print(n, &res);
	return (res);
}
