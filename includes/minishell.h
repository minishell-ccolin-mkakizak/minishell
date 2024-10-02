/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:33:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/03 07:17:45 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

int		minishell(char *command);
int		process_commands(char ***commands);
void	cd(char **command);
void	pwd(char **command);
char	***split_commands(char *input);
void	free_array(char **array);

#endif