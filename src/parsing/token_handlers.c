/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/23 13:46:14 by ccolin           ###   ########.fr       */
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

char	*continue_input_if_lst_tok_is_pipe(char *input, int i)
{
	i = skip_spaces_tabs(input, i);
	if (input[i])
		return(input);
	return (continue_input(input, ">"));
}

char	*remove_quotes(char *command, int i, int j, int *is_quoted_empty_string)
{
	char	*new_str;
	char	c;
	int		len;

	len = quoteless_strlen(command, 0, 0);
	if (len != ft_strlen(command))
		*is_quoted_empty_string = TRUE;
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
		{
			c = command[i++];
			while (command[i] && command[i] != c)
				new_str[j++] = command[i++];
			if (command[i])
				i++;
		}
		else
			new_str[j++] = command[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

int	quoteless_strlen(char *str, int i, int j)
{
	char	c;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
			{
				j++;
				i++;
			}
			if (str[i])
				i++;
		}
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

char*	expend_command_envps(char *command, t_env_list *envp, int *is_quoted_empty_string)
{
	command = find_envps(command, envp, TRUE);
	command = remove_quotes(command, 0, 0, is_quoted_empty_string);
	return (command);
}

int	command_token(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	int j;
	int	is_quoted_empty_string;

	is_quoted_empty_string = FALSE;
	j = i;
	while (input[j] && input[j] != ' ')
	{
		if (input[j] == '\'' || input[i] == '\"')
			go_to_end_of_quotes(input, &j, input[j]);
		j++;
	}
	token->token = ft_substr(input, i, j - i);
	i = j;
	token->type = COMMAND;
	token->token = expend_command_envps(token->token, lx_dt->envp, &is_quoted_empty_string);
	if(!is_quoted_empty_string && token->token[0] == 0)
	{
		free(token->token);
		return (tokenize(token, input, lx_dt, i));
	}
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

	j = i + 1;
	while (is_valid_key_char(input[j], FALSE))
		j++;
	token->token = ft_substr(input, i, j - i);
	i = j;
	token->type = lx_dt->next_token_type;
	return (next_token(token, input, lx_dt, ++i));
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
	if (token->type == PIPE)
	{
		lx_dt->expecting_command = TRUE;
		input = continue_input_if_lst_tok_is_pipe(input, i);
	}
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
