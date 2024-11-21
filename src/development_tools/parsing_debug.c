/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:24:10 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/20 17:03:05 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		printf("envp %d: %s\n", i, envp[i]);
		i++;
	}
}

const char	*getTokenTypeName(int type)
{
	switch (type)
	{
	case STRING_TYPE:
		return ("STRING");
	case COMMAND:
		return ("COMMAND");
	case SINGLE_QUOTE:
		return ("SINGLE_QUOTE");
	case DOUBLE_QUOTE:
		return ("DOUBLE_QUOTE");
	case INPUT_TYPE:
		return ("INPUT_TYPE");
	case OUTPUT_TYPE:
		return ("OUTPUT_TYPE");
	case HEREDOC:
		return ("HEREDOC");
	case APPEND:
		return ("APPEND");
	case PIPE:
		return ("PIPE");
	case ENVP:
		return ("ENVP");
	default:
		return ("UNKNOWN_TYPE");
	}
}

void	print_tokens(t_token *token)
{
	int i;

	if (!TABLE_DEBUG)
		return ;
	i = 1;
	while (1)
	{
		printf("Token %-5d\tString= %-20s\tType = %-15s\n\n", i, token->token, getTokenTypeName(token->type));
		if (!token->next)
			return ;
		token = token->next;
		i++;
	}
}