/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:17:15 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/20 17:40:35 by minoka           ###   ########.fr       */
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
