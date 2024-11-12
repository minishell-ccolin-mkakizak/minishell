/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:11:56 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/12 19:12:19 by mkakizak         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <minishell.h>

void exe_env(t_command *cmd, t_env_list *env)
{
	// need to add some error checking also formattig is not quit right
	print_env_list(env);
}