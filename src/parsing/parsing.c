/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:35:31 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/12 15:08:32 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lexer(t_token *token, t_lx_dt lx_dt, char *input)
{
	lx_dt.current_token = COMMAND;
	lx_dt.stack = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!lx_dt.stack)
		return ;
	lx_dt.stack[0] = '\0';
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
}

int	skip_spaces_tabs(char *input, int i)
{
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	return (i);
}

int	is_delimiter(char *input, int i)
{
	if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n' || \
		input[i] == '\'' || input[i] == '\"' || input[i] == '<' || \
		input[i] == '>' || input[i] == '|' || input[i] == '$' || \
		(input[i] == '<' && input[i + 1] == '<') || \
		(input[i] == '>' && input[i + 1] == '>'))
		return (1);
	return (0);
}

int	next_token_type(char *input, int i)
{
	if (input[i] == '\'')
		return (SINGLE_QUOTE);
	if (input[i] == '\"')
		return (DOUBLE_QUOTE);
	if (input[i] == '|')
		return (PIPE);
	if (input[i] == '<')
		return (INPUT);
	if (input[i] == '>')
		return (OUTPUT);
	if (input[i] == '$')
		return (ENVP);
	if (input[i] == '+' && input[i + 1] == '>')
		return (APPEND);
	if (input[i] == '<' && input[i + 1] == '<')
		return (HEREDOC);
	return (STRING);
}

void	single_quote_token(t_token *token, char *input, t_lx_dt lx_dt, int i)
{
	
}

void	double_quote_token(t_token *token, char *input, t_lx_dt lx_dt, int i)
{
	
}

void	envp_token(t_token *token, char *input, t_lx_dt lx_dt, int i)
{
	
}

void	dbl_char_opr_tok(t_token *token, char *input, t_lx_dt lx_dt, int i)
{
	token->token = malloc(sizeof(char) * (2 + 1));
	if (!token->token)
		return ;
	token->token[0] = input[i];
	token->token[1] = input[i];
	token->token[2] = '\0';
	token->type = lx_dt->next_token_type;
	i = i + 2;
	tokenize->next = malloc(sizeof(t_token));
	if (!tokenize->next)
		return (NULL);
	if (input[i])
		tokenize(token->next, input, lx_dt, i);
}

void	sngl_char_opr_tok(t_token *token, char *input, t_lx_dt lx_dt, int i)
{
	token->token = malloc(sizeof(char) * (1 + 1));
	if (!token->token)
		return ;
	token->token[0] = input[i];
	token->token[1] = '\0';
	token->type = lx_dt->next_token_type;
	i++;
	tokenize->next = malloc(sizeof(t_token));
	if (!tokenize->next)
		return (NULL);
	if (input[i])
		tokenize(token->next, input, lx_dt, i);
}

void	string_token(t_token *token, char *input, t_lx_dt lx_dt, int i)
{
	int		j;

	j = i;
	while (input[j] && !is_delimiter(input, j))
		j++;
	ft_substr(token->token, i, j - i);
	i = j;
	tokenize->next = malloc(sizeof(t_token));
	if (!token->next)
		return ;
	if (input[i])
		tokenize(token->next, input, lx_dt, i);
}

void	tokenize(t_token *token, char *input, t_lx_dt lx_dt, int i)
{
	i = skip_spaces_tabs(input, i);
	if (!input[i])
		return ;
	lx_dt->next_token_type = identify_lx_dt->next_token_type(input, i);
	if (lx_dt->next_token_type == SINGLE_QUOTE)
		single_quote_token(token, input, lx_dt, i);
	if (lx_dt->next_token_type == DOUBLE_QUOTE)
		double_quote_token(token, input, lx_dt, i);
	if (lx_dt->next_token_type == HEREDOC || \
		lx_dt->next_token_type == APPEND)
		dbl_char_opr_tok(token, input, lx_dt, i);
	if (lx_dt->next_token_type == INPUT_TOKEN || \
		lx_dt->next_token_type == OUTPUT_TOKEN || \
		lx_dt->next_token_type == PIPE)
		sngl_char_opr_tok(token, input, lx_dt, i);
	if (lx_dt->next_token_type == STRING)
		string_token(token, input, lx_dt, i);
	return ;
}

void	lex(char *input)
{
	t_token		*token;
	t_lx_dt	lx_dt;

	init_lexer(tokens, lx_dt, input);
	tokenize(token, input, lx_dt, 0);
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
		prompt = prompt(hostname);
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

// free and exit if failed malloc 
// substr malloc failsafe