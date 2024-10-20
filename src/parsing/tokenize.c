/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:35:13 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/20 23:16:50 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key_char(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||\
	(c >= '0' && c <= '9') || c == '_');
}

char	*expend_envp(char *token, char **envp)
{
	// int	i;

	// i = 0;
	// while (token[i])
	// {
	// 	if (token[i] != '$')
	// 		i++;
		
	// }
	return (token);
}

char	*remove_quotes(char *token)
{
	int		len;
	int		i;
	int		j;
	char	*new_token;

	i = 1;
	j = 0;
	len = ft_strlen(token);
	new_token = malloc(sizeof(char) * ((len - 2) + 1));
	while(i < len - 1)
		new_token[j++] = token[i++];
	new_token[j] = '\0';
	free(token);
	return (new_token);
}

char	**add_token(char **tokens, char *input, int strt, int *i)
{
	char	c;

	if (*i > strt && input[*i] == ' ')
		tokens = add_str_to_arr(tokens, ft_substr(input, strt, *i - strt));
	else if ((input[*i] == '|' && input[(*i) + 1] != '|') || (input[*i] == '<'\
	&& input[(*i) + 1] != '<') || (input[*i] == '>' && input[(*i) + 1] != \
	'>') || input[*i] == '(' || input[*i] == ')')
	{
		c = input[*i];
		if (*i > strt)
			tokens = add_str_to_arr(tokens, ft_substr(input, strt, *i - strt));
		tokens = add_str_to_arr(tokens, char_to_string(c));
	}
	else if ((input[*i] == '|' && input[(*i) + 1] == '|') || (input[*i] == '&'\
	&& input[(*i) + 1] == '&') || (input[*i] == '<' && input[(*i) + 1] == \
	'<') || (input[*i] == '>' && input[(*i) + 1] == '>'))
	{
		c = input[*i];
		if (*i > strt)
			tokens = add_str_to_arr(tokens, ft_substr(input, strt, *i - strt));
		tokens = add_str_to_arr(tokens, char_to_double_string(c));
		(*i)++;
	}
	return (tokens);
}

char	**refine_tokens(char **tokens, int i, char **envp)
{
	while (tokens[i])
	{
		if (tokens[i][0] == '\'')
			tokens[i] = remove_quotes(tokens[i]);
		else if (tokens[i][0] == '"')
		{
			tokens[i] = remove_quotes(tokens[i]);
			tokens[i] = expend_envp(tokens[i], envp);
		}
		else
			tokens[i] = expend_envp(tokens[i], envp);
		i++;
	}
	return (1);
}

char	**tokenize(char *input, int i)
{
	char	**tokens;
	int		strt;

	tokens = NULL;
	strt = i;
	while (input[i])
	{
		skip_over_quotes(input, &i);
		if (ft_strchr(" |<>()", input[i]))
		{
			tokens = add_token(tokens, input, strt, &i);
			strt = i + 1;
		}
		i++;
	}
	if (strt < i)
		tokens = add_str_to_arr(tokens, ft_substr(input, strt, i - strt));
	return (tokens);
}
