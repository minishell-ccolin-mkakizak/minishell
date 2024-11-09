/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:32:16 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/09 12:55:07 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lexer(t_token *tokens, t_lex_data lex_data, char *input)
{
	lex_data.current_token = COMMAND;
	lex_data.stack = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!lex_data.stack)
		return ;
	lex_data.stack[0] = '\0';
}

void	add_c_to_tok(t_token *token, char c)
{
	char	*new_token;
	int		i;

	if (!token->token)
		return ;
	i = 0;
	new_token = malloc(sizeof(char) * (ft_strlen(token->token) + 2));
	if (!new_token)
		return ;
	while (token->token[i])
	{
		new_token[i] = token->token[i];
		i++;
	}
	new_token[i++] = c;
	new_token[i] = '\0';
	free(token->token);
	token->token = new_token;
}

void	continue_token(t_token *token, char *input, t_lex_data lex_data, int i)
{
	if (input[i])
	{
		add_c_to_tok(token, input[i++]);
		tokenize(token, input, parser_data, i);
	}
}

int	skip_spaces_tabs(char *input, int i)
{
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	return (i);
}

void	tokenize(t_token *token, char *input, t_lex_data lex_data, int i)
{
	if (!input[i])
		return ;
	i = skip_spaces_tabs(input, i);
	continue_token(token, input, lex_data, i);
}

void	lex(char *input)
{
	t_token		*token;
	t_lex_data	lex_data;

	init_lexer(tokens, lex_data, input);
	tokenize(token, input, parser_data, 0);
	printf("%s", token->token);
	// add_history(input);
	free(input);
	return ;
}

int	main_parsing(char **envp)
{
	char			*prompt;
	char			*hostname;
	char			*input;
	// t_cmnd_tbl	command_table;

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
