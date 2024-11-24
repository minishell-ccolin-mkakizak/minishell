/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:17:15 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/21 16:32:47 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int is_match(char *str1, char *str2)
{
	if(ft_strncmp(str1, str2, ft_strlen(str1)) == 0)
		return (TRUE);
	else
		return (FALSE);
}

int get_array_len(char **array)
{	int i;

	i = 0;
	if(array ==  NULL)
		return(0);
	while(array[i])
	{
		i++;
	}
	return (i);
}

int	print_str_arr(char **arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_printf("[%d]:%s\n", i, arr[i]);
		i++;
	}
	return (0);
}