/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:05:47 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/23 14:22:34 by ccolin           ###   ########.fr       */
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

	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	cpy = (char *)malloc(sizeof(char) * (length + 1));
	if (cpy == NULL)
		return (NULL);
	ft_strcpy(cpy, s);
	return (cpy);
}
