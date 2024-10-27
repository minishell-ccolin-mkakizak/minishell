/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:04:40 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/27 14:15:13 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_execution(char **envp)
{
	t_cmnd_tbl	table;


	ft_printf("Starting execution mode\n-------------\n\n");
	init_cmnd_tbl(&table);
	print_cmnd_tbl(&table);
	return (0);
}
