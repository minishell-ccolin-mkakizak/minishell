/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:15:13 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/30 11:24:02 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exe_exit(t_command *cmd, t_cmnd_tbl *table)
{
	ft_printf("exit\n");
	exit(EXIT_SUCCESS);
}
