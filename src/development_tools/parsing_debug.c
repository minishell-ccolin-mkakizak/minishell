/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:24:10 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/10 15:24:07 by ccolin           ###   ########.fr       */
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

const char	*gettokentypebame(int type)
{
	if (type == STRING_TYPE)
		return ("STRING");
	else if (type == COMMAND)
		return ("COMMAND");
	else if (type == SINGLE_QUOTE)
		return ("SINGLE_QUOTE");
	else if (type == DOUBLE_QUOTE)
		return ("DOUBLE_QUOTE");
	else if (type == INPUT_TYPE)
		return ("INPUT_TYPE");
	else if (type == OUTPUT_TYPE)
		return ("OUTPUT_TYPE");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == ENVP)
		return ("ENVP");
	else
		return ("UNKNOWN_TYPE");
}

void	print_tokens(t_token *token)
{
	int	i;

	if (!TABLE_DEBUG)
		return ;
	i = 1;
	while (1)
	{
		printf("Token %-5d\tString= %-20s\tType = %-15s\n\n", i, token->token,
			gettokentypebame(token->type));
		if (!token->next)
			return ;
		token = token->next;
		i++;
	}
}
