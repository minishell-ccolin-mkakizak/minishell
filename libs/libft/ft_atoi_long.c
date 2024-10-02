/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:19:41 by mkakizak          #+#    #+#             */
/*   Updated: 2024/09/23 18:44:10 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_whitespaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
	{
		i++;
	}
	return (i);
}

static int	get_sign(const char *str, int i, long long *sign)
{
	*sign = 1;
	if (str[i] == '-')
	{
		*sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}
	return (i);
}

static long long	is_long_max_min(long long res, long sign, char c)
{
	if (sign == 1)
	{
		if (res > (LONG_MAX - c - '0') / 10)
		{
			error();
			return ((int)LONG_MAX);
		}
	}
	else if (sign == -1)
	{
		if (-res < (LONG_MIN + c - '0') / 10)
		{
			error();
			return ((int)LONG_MIN);
		}
	}
	return (res);
}

static long long	convert_to_long(const char *str, int i, long long sign)
{
	long long	res;
	long long	prev_res;

	res = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
		{
			prev_res = res;
			res = is_long_max_min(res, sign, str[i]);
			if (prev_res == res)
				res = res * 10 + str[i] - '0';
			else
				return (res);
		}
		else
		{
			if (!(str[i] == ' '))
				error();
			return (res * sign);
		}
		i++;
	}
	return (res * sign);
}

long	ft_atoi_long(const char *str)
{
	int			i;
	long long	sign;
	long long	res;

	i = skip_whitespaces(str);
	if (str[i] == '\0')
		error();
	i = get_sign(str, i, &sign);
	if (!ft_strncmp(str, "9223372036854775806", 21))
		return (-2 * sign);
	res = 0;
	res = convert_to_long(str, i, sign);
	return (res);
}
