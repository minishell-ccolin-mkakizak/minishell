/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:39:52 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/02 22:59:52 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **command)
{
	if (command[2])
	{
		ft_printf("cd: Too many arguments\n");
		return ;
	}
	if (chdir(command[1]))
		ft_printf("cd : %s: No such file or directory\n", command[1]);
}

void	pwd(char **command)
{
	char	*path;
	
	(void)command; // Will need to use command to check for pipe or redirection
	path = getcwd(NULL, 0);
	ft_printf("%s\n", path);
	free(path);
}
