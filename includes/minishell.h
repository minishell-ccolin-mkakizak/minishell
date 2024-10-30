/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:19:33 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/30 13:00:05 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

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
	char				*heredoc_delimiter;
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
	int			exit_shell;
	char		**envp;
}				t_cmnd_tbl;

//file_discripters

typedef struct s_fd
{
	int stdin_backup;
	int stdout_backup;
	int pipe_fd[2];
}	t_fd;

//token
typedef struct s_token
{
	char	*token;
	int		type;
}			t_token;

# define COMMAND 1
# define ARGUMENT 2
# define OPERATOR 3

//check if on mac or linux
# ifdef __APPLE__
#  define IS_LINUX 0
# endif
# ifndef IS_LINUX
#  define IS_LINUX 1
# endif

# define HSTNM_MAC "/Library/Preferences/SystemConfiguration/preferences.plist"
# define HOSTNAME_LINUX "/etc/hostname"

//input/output for pipe fds
# define INPUT 0
# define OUTPUT 1

//DEVELOPMENT TOOLS
//mock_comand_table.c
void		add_environment_variables(t_cmnd_tbl *table);
int			get_env_count(void);
char		*get_env_variable(void);
void		init_cmnd_tbl(t_cmnd_tbl *table);
void		setup_table_defaults(t_cmnd_tbl *table);
void		handle_commands_interactive(t_cmnd_tbl *table);
t_command	*prompt_command(void);
t_command	*create_command(void);
void		fill_command_args(t_command *cmd);
void		fill_command_files(t_command *cmd);
void		fill_command_flags(t_command *cmd);
void		add_command_interactive(t_cmnd_tbl *table);
void		print_command(t_command *cmd);
void		print_command_args(t_command *cmd);
void		print_command_details(t_command *cmd);
void		print_cmnd_tbl(t_cmnd_tbl *table);
void		print_environment_variables(t_cmnd_tbl *table);
void		print_commands(t_cmnd_tbl *table);
t_command	*prompt_command(void);
void		add_command_interactive(t_cmnd_tbl *table);
void		print_command(t_command *cmd);
void		print_cmnd_tbl(t_cmnd_tbl *table);

//parsing_debug.c
void		print_envp(char **envp);

//EXECUTION
//execution.c
int			main_execution(char *envp[]);

//pipeline.c
int 		execute_pipeline(t_cmnd_tbl *table, char *envp[]);

//execute_command.c
char		*validate_path(char **path_arr, char *cmd);
char		*find_path(char *cmd, char *envp[]);
int			execute_cmd(t_command *cmd, char *envp[]);

//pipeline_utils.c
void		throw_error(char *message, int exit_status, int error_number);
pid_t		safe_fork(void);
void		init_fd(t_fd *fd);
void		restore_fd(t_fd *fd);
void		init_pipe(t_fd *fd);

//mock_data.c
t_command 	*create_mock_commands_0(void);
t_command 	*create_mock_commands_1(void);
t_command 	*create_mock_commands_2(void);
void 		free_commands(t_command *cmd);

//PARSING
//parsing.c
int			main_parsing(char **envp);

//parsing_utils.c
char		*remove_quotes(char *p_tok);
int			array_size(char **array);
char		*char_to_string(char c);
char		*char_to_double_string(char c);


//PROMPT
//build_prompt.c
char		*build_prompt(char *hostname);

//prompt_linux.c
char		*get_linux_hostname(void);
char		*get_current_dir(const char *path, char delimiter);
char		*get_hostname(void);
char		*get_prompt_suffix(void);
char		*colon_or_space(void);

//prompt_mac.c
char		*get_dir_mac(const char *path, char delimiter);
char		*extract_mac_hostname(int fd);
char		*parse_mac_hostname(char *line);


#endif