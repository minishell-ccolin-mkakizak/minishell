/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:04:40 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/19 16:06:11 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_execution(void)
{
	t_command_table	table;

	ft_printf("Starting execution mode\n-------------\n\n");
	init_command_table(&table);
	print_command_table(&table);
	return (0);
}
