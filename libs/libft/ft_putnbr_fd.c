/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:34:56 by mkakizak          #+#    #+#             */
/*   Updated: 2024/05/03 13:57:57 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursive_print( int num, int fd )
{
	char	print;

	if (num >= 10)
	{
		recursive_print (num / 10, fd);
		print = num % 10 + '0';
		write(fd, &print, 1);
	}
	else if (num < 10)
	{
		print = num % 10 + '0';
		write(fd, &print, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n > INT_MIN)
		{
			write(fd, "-", 1);
			n = n * -1;
			recursive_print(n, fd);
		}
		else if (n == -2147483648)
		{
			write(fd, "-2147483648", 11);
		}
	}
	else
	{
		recursive_print(n, fd);
	}
}
