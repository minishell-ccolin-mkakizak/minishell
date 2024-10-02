/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:05:47 by mkakizak          #+#    #+#             */
/*   Updated: 2024/05/06 19:40:44 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;
	size_t	src_length;

	src_length = ft_strlen(src);
	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_length);
}

char	*ft_strdup(const char *s)
{
	size_t	length;
	char	*cpy;

	length = ft_strlen(s);
	cpy = (char *)malloc(sizeof(char) * (length + 1));
	if (cpy == NULL)
		return (NULL);
	ft_strcpy(cpy, s);
	return (cpy);
}
