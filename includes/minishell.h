/* ************************************************************************** */
<<<<<<< Updated upstream
/*                                      */
/*                            :::     ::::::::   */
/*   minishell.h                                        :+:   :+:    :+:   */
/*                          +:+ +:+       +:+    */
/*   By: ccolin <ccolin@student.42.fr>        +#+  +:+       +#+    */
/*                        +#+#+#+#+#+   +#+     */
/*   Created: 2024/10/02 14:33:50 by ccolin   #+#  #+#          */
/*   Updated: 2024/10/06 12:57:07 by ccolin     ###   ########.fr    */
/*                                      */
=======
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:33:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/14 14:04:06 by minoka           ###   ########.fr       */
/*                                                                            */
>>>>>>> Stashed changes
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

# include <readline/readline.h>
# include <readline/history.h>

//command table 
typedef struct s_command
{
	char				**args;
	char				*input_file;
	char				*output_file;
	int					append;
	int					pipe_in;
	int					pipe_out;
	int					exec_cond;
	int					is_builtin;
	struct s_command	*next;
}						t_command;

typedef struct s_command_table
{
	t_command	*head;
	int			exit_status;
	char		**envp;
}				t_command_table;

//check if on mac or linux
# ifdef __APPLE__
#  define IS_LINUX 0
# endif
# ifndef IS_LINUX
#  define IS_LINUX 1
# endif

# define HOSTNAME_MAC \
"/Library/Preferences/SystemConfiguration/preferences.plist"
# define HOSTNAME_LINUX "/etc/hostname"

//input/output for pipe fds
# define INPUT 0
# define OUTPUT 1

//minishell.c
int		minishell(char *command);

//build_prompt.c
char	*build_prompt(char *hostname);

//prompt_linux.c
char	*get_linux_hostname(void);
char	*get_current_dir(const char *path, char delimiter);
char	*get_hostname(void);
char	*get_prompt_suffix(void);
char	*colon_or_space(void);

//prompt_mac.c
char	*get_dir_mac(const char *path, char delimiter);
char	*extract_mac_hostname(int fd);
char	*parse_mac_hostname(char *line);

//process_commands.c
int		process_commands(char ***commands);

// split_commands.c
char	***split_commands(char *input);

//commands.c
void	cd(char **command);
void	pwd(char **command);

//pip_utils.c
int		free_all(char **str_arr);
void	throw_error(char *message, int exit_status, int error_number);
char	**parse_cmd(int argc, char *argv[]);
char	*validate_path(char **path_arr, char *cmd);
char	*find_path(char *cmd);
void 	execute_cmd(char **cmd);

//pipe.c
int		my_pipe(int argc, char *argv[], char *envp[]);

#endif