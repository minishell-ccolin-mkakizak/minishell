/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:23:49 by mkakizak          #+#    #+#             */
/*   Updated: 2024/05/12 17:15:53 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	recursive_print(unsigned long n, int *r, char *b, unsigned long b_l)
{
	char	print;

	if (n >= b_l)
	{
		recursive_print (n / b_l, r, b, b_l);
		print = b[n % b_l];
		write(1, &print, 1);
		*r += 1;
	}
	else if (n < b_l)
	{
		print = b[n % b_l];
		if (write(1, &print, 1) != -1)
			*r += 1;
		else
			return (-1);
	}
	return (0);
}

int	ft_putnbr_base(unsigned long n, char *b)
{
	unsigned long	b_l;
	int				r;

	b_l = (unsigned long)ft_strlen(b);
	r = 0;
	if (recursive_print(n, &r, b, b_l) == -1)
		return (-1);
	return (r);
}
