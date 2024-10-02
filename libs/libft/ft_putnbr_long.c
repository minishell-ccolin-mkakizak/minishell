/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:06:05 by minokakakiz       #+#    #+#             */
/*   Updated: 2024/07/02 18:22:57 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursive_print( long long num, int *res)
{
	char	print;

	if (num >= 10)
	{
		recursive_print (num / 10, res);
		print = num % 10 + '0';
		write(1, &print, 1);
		*res += 1;
	}
	else if (num < 10)
	{
		print = num % 10 + '0';
		write(1, &print, 1);
		*res += 1;
	}
}

int	ft_putnbr_long(long long n)
{
	int	res;

	res = 0;
	if (n < 0)
	{
		if (n > LONG_MIN)
		{
			if (write(1, "-", 1) != -1)
			{
				n = n * -1;
				res += 1;
				recursive_print(n, &res);
			}
			else
				return (-1);
		}
		else if (n == -9223372036854775807)
		{
			write(1, "-9223372036854775807", 10);
			res = 20;
		}
	}
	else
		recursive_print(n, &res);
	return (res);
}
