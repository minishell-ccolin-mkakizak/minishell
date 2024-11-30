/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:35:31 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/30 12:55:58 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(char **input, t_cmnd_tbl *command_table)
{
	t_token	*token;
	t_lx_dt	*lexer_data;
	int		return_value;

	lexer_data = malloc(sizeof(t_lx_dt));
	if (!lexer_data)
		return (alloc_failed());
	return_value = init_lexer(&token, lexer_data, command_table);
	if (!return_value)
		return_value = tokenize(token, input, lexer_data, 0);
	if (!return_value)
		expend_envps(token, command_table->envp,
			command_table->last_exit_status);
	print_tokens(token);
	add_history(*input);
	free(*input);
	if (!return_value)
	{
		if (build_command_table(token, command_table))
			return_value = ALLOCATION_FAIL;
		print_cmnd_tbl(command_table);
	}
	free_parser_data(token, lexer_data);
	return (return_value);
}
