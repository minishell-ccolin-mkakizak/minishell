/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:22:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/06 12:57:36 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_prompt2(char *prompt, int total_len, char *hstam, char *cur_dir)
{
	ft_strlcpy(prompt, getenv("USER"), total_len);
	ft_strlcat(prompt, "@", total_len);
	ft_strlcat(prompt, hstam, total_len);
	ft_strlcat(prompt, colon_or_space(), total_len);
	ft_strlcat(prompt, cur_dir, total_len);
	ft_strlcat(prompt, get_prompt_suffix(), total_len);
}

/* Builds and returns the complete prompt */
char	*build_prompt(char *hostname)
{
	char	*prompt;
	char	*current_dir;
	int		total_len;
	char	*path;

	path = getcwd(NULL, 0);
	current_dir = get_current_dir(path, '/');
	total_len = ft_strlen(getenv("USER")) + ft_strlen(current_dir) \
		+ ft_strlen(hostname) + ft_strlen(get_prompt_suffix()) + 3;
	prompt = malloc(total_len);
	if (!prompt)
	{
		free(path);
		free(current_dir);
		return (NULL);
	}
	build_prompt2(prompt, total_len, hostname, current_dir);
	free(path);
	free(current_dir);
	return (prompt);
}
