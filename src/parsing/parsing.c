/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:35:31 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/23 11:37:41 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expend_envp(char *str, t_env_list *envp)
{
	int		name_len;
	while (envp)
	{
		name_len = ft_strlen(envp->name);
		if (name_len == ft_strlen(str) && !ft_strncmp(envp->name, str, name_len))
		{
			free(str);
			str = ft_strdup(envp->value);
			break ;
		}
		envp = envp->next;
	}
	if (!envp)
	{
		free(str);
		str = ft_strdup("");
	}
	return (str);
}

char	*replace_substring_with_envp(char *str, int start, int end,t_env_list *envp)
{
	char	*prefix;
	char	*variable;
	char	*suffix;
	prefix = ft_substr(str, 0, start);
	variable = expend_envp(ft_substr(str, start + 1, end - start), envp);
	suffix = ft_substr(str, end + 1, ft_strlen(str));
	free(str);
	if (prefix[0] != 0)
		str = ft_strjoin(prefix, variable);
	else
		str = ft_strdup(variable);
	if (suffix[0] != 0)
		str = ft_strjoin(str, suffix);
	free(prefix);
	free(variable);
	free(suffix);
	return (str);
}


int	handle_quotes(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'' && *in_squote)
		*in_squote = FALSE;
	if (c == '\'' && !*in_squote && !in_dquote)
		*in_squote = TRUE;
	if (c == '\"' && *in_dquote)
		*in_dquote = FALSE;
	if (c == '\"' && !*in_dquote && !in_squote)
		*in_dquote = TRUE;
	return (*in_squote);
}

static char	*process_env_var(char *str, t_env_list *envp, int start)
{
	int end;
	end = start + 1;
	while (str[start] && is_valid_key_char(str[end], FALSE))
		end++;
	return (replace_substring_with_envp(str, start, end - 1, envp));
}

char	*find_envps(char *str, t_env_list *envp, int is_command)
{
	int	i = 0, in_squote = 0, in_dquote = 0;
	while (str[i])
	{
		if (is_command && handle_quotes(str[i], &in_squote, &in_dquote))
		{
			i++;
			continue;
		}
		if (str[i] == '$' && is_valid_key_char(str[i + 1], TRUE) && (!is_command || !in_squote))
		{
			str = process_env_var(str, envp, i);

			i = 0;
		}
		else
			i++;
	}
	return (str);
}



void	expend_envps(t_token *token, t_env_list *envp)
{
	while (token)
	{
		if (token && token->type == HEREDOC)
			token = token->next->next;
		if (token && token->type == ENVP || token->type == STRING_TYPE |token->type == DOUBLE_QUOTE)
			token->token = find_envps(token->token, envp, FALSE);
		token = token->next;
	}
}

int	parse(char *input, t_cmnd_tbl *command_table)
{
	t_token	*token;
	t_lx_dt	*lx_dt;
	int		parser_error;

	lx_dt = malloc(sizeof(t_lx_dt));
	if (!lx_dt)
		return (0);
	token = malloc(sizeof(t_token));
	if (!token)
		return (0);
	init_lexer(&token, lx_dt, input, command_table);
	parser_error = tokenize(token, input, lx_dt, 0);
	expend_envps(token, command_table->envp);
	print_tokens(token);
	add_history(input);
	free(input);
	if (!parser_error)
	{
		build_command_table(token, command_table);
		print_cmnd_tbl(command_table);
	}
	free_parser_data(token, lx_dt);
	return (parser_error);
}
