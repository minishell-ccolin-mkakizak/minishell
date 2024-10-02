/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:29:28 by mkakizak          #+#    #+#             */
/*   Updated: 2024/07/02 18:02:05 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	is_smaller(int a, int b)
{
	if (a < b)
		return (TRUE);
	return (FALSE);
}

int	is_bigger(int a, int b)
{
	if (a > b)
		return (TRUE);
	return (FALSE);
}

int	find_min_index(int *arr, int len)
{
	int	i;
	int	temp;
	int	res;

	temp = INT_MAX;
	i = 0 ;
	res = -1;
	while (i < len)
	{
		if (is_smaller(arr[i], temp))
		{
			temp = arr[i];
			res = i;
		}
		i++;
	}
	return (res);
}

void	fill_last(int *arr, int len, int last_nbr)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (arr[i] == 0)
			arr[i] = last_nbr;
		i++;
	}
}

int	*compress(int *arr, int len)
{
	int	*res;
	int	i;
	int	j;
	int	min_i;

	res = ft_calloc(sizeof(int), len);
	if (res == NULL)
		error();
	i = 0;
	j = 1;
	while (i < len)
	{
		min_i = find_min_index(arr, len);
		if (min_i != -1)
		{
			res[min_i] = j++;
			arr[min_i] = INT_MAX;
		}
		i++;
	}
	fill_last(res, len, j);
	return (free(arr), res);
}
