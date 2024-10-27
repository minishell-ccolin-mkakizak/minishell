/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:32:16 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/27 17:24:27 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lexer(t_token *tokens, t_lexer_data lexer_data, char *input)
{
	tokens = NULL;
	lexer_data->current_token = NULL;
	lexer_data->expected_token = COMMAND;
	lexer_data->stack = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!lexer_data->stack)
		return (NULL);
}

int	tokens_size(t_tokens *tokens)
{
	int		i;
	
	i = 0;
	
	return (0);
}

void	alloc_tokens(t_tokens *tokens)
{
	if (!tokens)
		tokens = malloc(sizeof(t_tokens) * (tokens_size(&tokens) + 1));
	if (!tokens)
		return (NULL);
}

void	tokenize(t_token *tokens, char *input, t_lexer_data lexer_data, int i)
{
	alloc_token(tokens);
}

void	lex(char *input)
{
	t_token			*tokens;
	t_lexer_data	lexer_data;

	init_lexer(tokens, lexer_data, input);
	tokenize(tokens, input, parser_data, 0);
	// add_history(input);
	free(input);
	return ;
}

int	main_parsing(char **envp)
{
	char			*prompt;
	char			*hostname;
	char			*input;
	char			**p_toks;
	t_cmnd_tbl	command_table;

	ft_printf("Starting parsing mode\n");
	hostname = get_hostname();
	chdir(getenv("HOME"));
	while (1)
	{
		prompt = build_prompt(hostname);
		input = readline(prompt);
		if (!input)
		{
			free(prompt);
			break ;
		}
		free(prompt);
		lex(input);
	}
	clear_history();
	free(hostname);
	ft_printf("Exiting...\n");
	return (0);
}
