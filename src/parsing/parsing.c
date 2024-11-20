/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:35:31 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/20 21:03:49 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(char *input, t_cmnd_tbl *command_table)
{
	t_token	*token;
	t_lx_dt	*lx_dt;
	int		parser_error;

	lx_dt = malloc(sizeof(t_lx_dt));
	if (!lx_dt)
		return (0);
	token = malloc(sizeof(t_token));
	if (!token)
		return (0);
	init_lexer(&token, lx_dt, input);
	parser_error = tokenize(token, input, lx_dt, 0);
	// expend_envps(token);
	print_tokens(token);
	add_history(input);
	free(input);
	if (!parser_error)
	{
		build_command_table(token, command_table);
		print_cmnd_tbl(command_table);
	}
	free_parser_data(token, lx_dt);
	return (parser_error);
}
