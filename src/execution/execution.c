/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:04:40 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/27 17:19:16 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_execution(char **envp)
{
	t_cmnd_tbl	*table;

	table = ft_calloc(sizeof table, 1);
	if(!table)
		return (-1);

	ft_printf("Starting execution mode\n-------------\n\n");
	table->head = create_mock_commands();
	print_cmnd_tbl(table);
	return (0);
}
