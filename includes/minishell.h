/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:33:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/03 09:19:03 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

//input/output for pipe fds
# define INPUT 0
# define OUTPUT 1

int		minishell(char *command);
int		process_commands(char ***commands);
void	cd(char **command);
void	pwd(char **command);
char	***split_commands(char *input);

//pip_utils.c
int		free_all(char **str_arr);
void	throw_error(char *message, int exit_status, int error_number);
char	**parse_cmd(int argc, char *argv[]);
char	*validate_path(char **path_arr, char *cmd);
char	*find_path(char *cmd, char *envp[]);

//pipe.c
int	my_pipe(int argc, char *argv[], char *envp[]);

#endif