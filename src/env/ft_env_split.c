/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:18:45 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/11 14:00:08 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_env_split(char const *str)
{
	char	**result;
	char	*equal_sign;

	result = malloc(3 * sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = NULL;
	result[1] = NULL;
	result[2] = NULL;
	equal_sign = strchr(str, '=');
	if (!equal_sign)
	{
		result[0] = strdup(str);
		return (result);
	}
	result[0] = ft_strtrim(str, equal_sign);
	result[1] = ft_strdup(equal_sign + 1);
	return (result);
}
