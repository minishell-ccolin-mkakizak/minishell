/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/16 17:42:18 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_valid_key_char(char c, int is_first_char)
{
	if (is_first_char)
		return (ft_isalpha(c) || c == '_' || c == '?');
	else
		return (ft_isalnum(c) || c == '_' || c == '?');
}

int	skip_spaces_tabs(char *input, int i)
{
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	return (i);
}

int	is_delimiter(char *input, int i)
{
	if (input[i] == ' ' || input[i] == '\0' || input[i] == '\t'
		|| input[i] == '\n' || input[i] == '\'' || input[i] == '\"'
		|| input[i] == '<' || input[i] == '>' || input[i] == '|'
		|| (input[i] == '$' && is_valid_key_char(input[i + 1], TRUE)))
		return (1);
	return (0);
}