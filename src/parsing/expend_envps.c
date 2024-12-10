/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_envps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:54:57 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/10 17:55:45 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expend_envp(char *str, t_env_list *envp)
{
	size_t	name_len;

	while (envp)
	{
		name_len = ft_strlen(envp->name);
		if (name_len == ft_strlen(str) && !ft_strncmp(envp->name, str,
				name_len))
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

static char	*find_end_of_env_key(char *str, t_env_list *envp, int start,
		int last_exit_status)
{
	int	end;

	end = start + 1;
	if (str[end] == '?')
		return (replace_substring_with_exit_status(str, start, end,
				last_exit_status));
	while (str[start] && is_valid_key_char(str[end], FALSE))
		end++;
	return (replace_substring_with_envp(str, start, end - 1, envp));
}

/*=============================================================================
Finds the start of an env key and calls find_end_of_env_key which will find
the end and expend the envp. The reason why the command token gets special
treatment is because it can be composed of several quoted parts, contrary
to other tokens who have their quotes removed at tokenization time and get
the double or single quote type.
=============================================================================*/
char	*find_envps(char *str, t_env_list *envp, int is_command,
		int last_exit_status)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (is_command)
			set_quotes_flags(str[i], &in_squote, &in_dquote);
		if ((str[i] == '$' && (is_valid_key_char(str[i + 1], TRUE) || str[i
					+ 1] == '?')) && (!is_command || !in_squote))
		{
			str = find_end_of_env_key(str, envp, i, last_exit_status);
			i = 0;
			in_squote = 0;
			in_dquote = 0;
		}
		else
			i++;
	}
	return (str);
}

/*=============================================================================
envps can be expended from any non-operator token with the exception of the
heredoc delimiter whether it is quoted or not.
=============================================================================*/
void	expend_envps(t_token *token, t_env_list *envp, int last_exit_status)
{
	while (token)
	{
		if (token && token->type == HEREDOC)
			token = token->next->next;
		if (token && (token->type == ENVP || token->type == STRING_TYPE
				|| token->type == DOUBLE_QUOTE))
			token->token = find_envps(token->token, envp, FALSE,
					last_exit_status);
		if (token)
			token = token->next;
	}
}
