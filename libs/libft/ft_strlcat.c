/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:20:25 by mkakizak          #+#    #+#             */
/*   Updated: 2024/05/15 11:40:05 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find(size_t dstsize, size_t dst_l, size_t src_l, size_t *cut_l)
{
	if (dstsize > dst_l)
	{
		*cut_l = dstsize - dst_l - 1;
		return (src_l + dst_l);
	}
	else
	{
		return (src_l + dstsize);
	}
}

static int	concat(char *dst, const char *src, size_t cut_l, size_t dst_l)
{
	size_t	i;

	i = 0;
	while (i < cut_l && src[i] != '\0')
	{
		dst[i + dst_l] = src[i];
		i++;
	}
	if (cut_l)
		dst[i + dst_l] = '\0';
	return (0);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_l;
	size_t	dst_l;
	size_t	res;
	size_t	cut_l;

	res = 0;
	if (dstsize == 0)
	{
		if (src != NULL)
			return (ft_strlen(src));
		return (dstsize);
	}
	src_l = ft_strlen(src);
	dst_l = ft_strlen(dst);
	cut_l = 0;
	res = find(dstsize, dst_l, src_l, &cut_l);
	concat(dst, src, cut_l, dst_l);
	return (res);
}
