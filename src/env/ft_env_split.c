/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:18:45 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/10 16:32:43 by mkakizak         ###   ########.fr       */
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
	result[0] = strndup(str, equal_sign - str);
	result[1] = strdup(equal_sign + 1);
	return (result);
}
