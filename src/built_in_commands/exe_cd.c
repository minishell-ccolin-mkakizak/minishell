/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:09:16 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/25 21:04:12 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void exe_cd(t_command *cmd, t_cmnd_tbl *table)
{
	// this needs error handling for more than 1 args
	// need to go to home if '~'

	char *home_dir;
	char *new_dir;

	home_dir = getenv("HOME");
	new_dir = NULL;

	if (cmd->args == NULL || cmd->args[0] == NULL)
	{
		chdir(home_dir);
		return;
	}
	else
	{
		char *path = cmd->args[0];

		if (path[0] == '~')
		{
			if (path[1] == '\0' || path[1] == '/')
			{
				if(path[2] == '\0')
				{
					puts("home with out path");
					chdir(home_dir);
				}
			}
			else
			{
				puts("home with path");
				// puts("does it make it here?");
				// new_dir = ft_calloc(ft_strlen(home_dir) + ft_strlen(path), sizeof(char));
				// // ft_strlcat(new_dir, home_dir, ft_strlen(home_dir));
				// // ft_strlcat(new_dir, &path[2], ft_strlen(home_dir));
				// ft_printf("new_dir: %s\n", new_dir);
				// chdir(new_dir);
				// free(new_dir);
				return;
			}
		}
		ft_printf("just path: %s\n", path);
		chdir(path);
	}
	puts("YOU MADE IT TO CD!!");
}
