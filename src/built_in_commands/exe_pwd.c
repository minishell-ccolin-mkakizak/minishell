/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:10:59 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/12 19:11:08 by mkakizak         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <minishell.h>

void exe_pwd(t_command *cmd, t_env_list *env)
{
	char *dir;

	dir = getcwd(NULL, 0);
	ft_printf("%s\n", dir);
}