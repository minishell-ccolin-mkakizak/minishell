/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:24:10 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/20 19:39:24 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		printf("Token %d: %s\n", i, tokens[i]);
		i++;
	}
}

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
