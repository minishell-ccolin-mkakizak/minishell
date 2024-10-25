/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:01:42 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/25 10:05:38 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key_char(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||\
	(c >= '0' && c <= '9') || c == '_');
}

char	*remove_quotes(char *p_tok)
{
	int		len;
	int		i;
	int		j;
	char	*new_p_tok;

	i = 1;
	j = 0;
	len = ft_strlen(p_tok);
	new_p_tok = malloc(sizeof(char) * ((len - 2) + 1));
	while(i < len - 1)
		new_p_tok[j++] = p_tok[i++];
	new_p_tok[j] = '\0';
	free(p_tok);
	return (new_p_tok);
}

char	**add_p_tok(char **p_toks, char *input, int strt, int *i)
{
	if (*i > strt && input[*i] == ' ')
		p_toks = add_str_to_arr(p_toks, ft_substr(input, strt, *i - strt));
	else if ((input[*i] == '|' && input[*i + 1] != '|') ||
	(input[*i] == '<' && input[*i + 1] != '<') ||
	(input[*i] == '>' && input[*i + 1] != '>') ||
	input[*i] == '(' || input[*i] == ')')
	{
		if (*i > strt)
			p_toks = add_str_to_arr(p_toks, ft_substr(input, strt, *i - strt));
		p_toks = add_str_to_arr(p_toks, char_to_string(input[*i]));
	}
	else if ((input[*i] == '|' && input[*i + 1] == '|') ||
	(input[*i] == '&' && input[*i + 1] == '&') ||
	(input[*i] == '<' && input[*i + 1] == '<') ||
	(input[*i] == '>' && input[*i + 1] == '>'))
	{
		if (*i > strt)
			p_toks = add_str_to_arr(p_toks, ft_substr(input, strt, *i - strt));
		p_toks = add_str_to_arr(p_toks, char_to_double_string(input[*i]));
		(*i)++;
	}
	return (p_toks);
}

char	**p_tokize(char *input, int i)
{
	char	**p_toks;
	int		strt;

	p_toks = NULL;
	strt = i;
	while (input[i])
	{
		skip_over_quotes(input, &i);
		if (input[i] == ' ' || ft_strchr("|<>()", input[i]) ||
			(input[i] == '&' && input[i + 1] == '&') ||
			(input[i] == '>' && input[i + 1] == '>') ||
			(input[i] == '<' && input[i + 1] == '<'))
		{
			p_toks = add_p_tok(p_toks, input, strt, &i);
			strt = i + 1;
		}
		i++;
	}
	if (strt < i)
		p_toks = \
		add_str_to_arr(p_toks, ft_substr(input, strt, i - strt));
	return (p_toks);
}
