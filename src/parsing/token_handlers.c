/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/20 22:56:46 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*continue_input(char *input, char *str)
{
	char	*line;
	char	*temp;

	line = readline(str);
	temp = ft_strjoin(input, "\n");
	free(input);
	input = ft_strjoin(temp, line);
	free(line);
	free(temp);
	return (input);
}

void	go_to_end_of_quotes(char *input, int *j, char c)
{
	int		i;
	
	i = *j;
	while(1)
	{
		i++;
		if (input[i] == c)
			break ;
		if (!input[i])
			input = continue_input(input, ">");
	}
	*j = i;
}

int	command_token(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	int j;

	j = i;
	while (input[j] && input[j] != ' ')
	{
		if (input[j] == '\'' || input[j] == '\"')
			go_to_end_of_quotes(input, &j, input[j]);
		j++;
	}
	token->token = ft_substr(input, i, j - i);
	i = j;
	token->type = COMMAND;
	lx_dt->expecting_command = FALSE;
	return (next_token(token, input, lx_dt, i));
}

int	single_quote_token(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	int	j;

	j = i;
	while (1)
	{
		j++;
		if (!input[j])
			continue_input(input, ">");
		if (input[j] == '\'')
			break;
	}
	token->token = ft_substr(input, i + 1, j - i - 1);
	i = j;
	token->type = lx_dt->next_token_type;
	i++;
	return (next_token(token, input, lx_dt, i));
}

int	double_quote_token(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	int	j;

	j = i;
	while (1)
	{
		j++;
		if (!input[j])
			continue_input(input, ">");
		if (input[j] == '\"')
			break;
	}
	token->token = ft_substr(input, i + 1, j - i - 1);
	i = j;
	token->type = lx_dt->next_token_type;
	i++;
	return (next_token(token, input, lx_dt, i));
}

int	envp_token(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	int	j;

	j = ++i;
	while (is_valid_key_char(input[j], FALSE))
		j++;
	token->token = ft_substr(input, i, j - i);
	i = j;
	token->type = lx_dt->next_token_type;
	return (next_token(token, input, lx_dt, i));
}

int	dbl_char_opr_tok(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{	
	token->token = malloc(sizeof(char) * (2 + 1));
	if (!token->token)
		return (0);
	token->token[0] = input[i];
	token->token[1] = input[i];
	token->token[2] = '\0';
	token->type = lx_dt->next_token_type;
	i = i + 2;
	return (next_token(token, input, lx_dt, i));
}

int	sngl_char_opr_tok(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	token->token = malloc(sizeof(char) * (1 + 1));
	if (!token->token)
		return (0);
	token->token[0] = input[i];
	token->token[1] = '\0';
	token->type = lx_dt->next_token_type;
	i++;
	if (lx_dt->next_token_type == PIPE)
		lx_dt->expecting_command = TRUE;
	return (next_token(token, input, lx_dt, i));
}

int	string_token(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	int j;

	j = i;
	while (input[j] && !is_delimiter(input, j))
		j++;
	token->token = ft_substr(input, i, j - i);
	i = j;
	token->type = lx_dt->next_token_type;
	return (next_token(token, input, lx_dt, i));
}