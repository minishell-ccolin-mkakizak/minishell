/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:45:57 by mkakizak          #+#    #+#             */
/*   Updated: 2024/05/03 13:56:58 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length(int n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	power(int base, int expo)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (i < expo)
	{
		res *= base;
		i++;
	}
	return (res);
}

static char	*fill_string(char *res, int n, int length, int is_neg)
{
	int	i;
	int	expo;

	expo = length - 1;
	i = 0;
	if (is_neg)
	{
		res[i] = '-';
		i++;
		expo--;
	}
	while (i < length)
	{
		res[i] = (n / power(10, expo)) + '0';
		n = n % power(10, expo);
		expo--;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		length;
	int		is_neg;

	is_neg = 0;
	length = get_length(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		is_neg = 1;
		n *= -1;
		length++;
	}
	res = malloc(sizeof(char) * (length + 1));
	if (res == NULL)
		return (NULL);
	res = fill_string(res, n, length, is_neg);
	return (res);
}
