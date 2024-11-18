/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:07:41 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/18 16:44:39 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void free_commands(t_command *cmd)
// {
//     t_command *temp;
//     int i;

//     while (cmd)
//     {
//         temp = cmd->next;

//         // Free args array
//         i = 0;
//         while (cmd->args && cmd->args[i])
//             free(cmd->args[i++]);
//         free(cmd->args);

//         // Free other allocated strings
//         free(cmd->input_file);
//         free(cmd->output_file);
//         free(cmd->heredoc_delimiter);

//         // Free the command structure itself
//         free(cmd);
//         cmd = temp;
//     }
// }