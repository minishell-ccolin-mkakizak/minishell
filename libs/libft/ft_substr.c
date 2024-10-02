/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:05:34 by mkakizak          #+#    #+#             */
/*   Updated: 2024/05/03 13:58:48 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_smaller(size_t num1, size_t num2)
{
	if (num1 < num2)
		return (num1);
	if (num1 > num2)
		return (num2);
	return (num2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;
	size_t			sub_length;

	sub_length = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	while (s[start + sub_length] != '\0')
		sub_length++;
	i = 0;
	res = ft_calloc(get_smaller(sub_length, len) + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	while (s[i + start] != '\0' && i < len)
	{
		res[i] = s[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}
