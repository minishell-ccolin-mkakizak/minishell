/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:19:33 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/20 23:13:34 by ccolin           ###   ########.fr       */
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
void		print_tokens(char **tokens);
void		print_envp(char **envp);

//EXECUTION
//execution.c
int			main_execution(void);

//PARSING
//are_quotes_closed.c
char		*are_quotes_closed(char *input);
char		*continue_input(char *input);
//parsing.c
int			main_parsing(char **envp);
//tokenize_utils.c
void		skip_over_quotes(char *input, int *i);
int			array_size(char **array);
char		**add_str_to_arr(char **array, char *new_string);
char		*char_to_string(char c);
char		*char_to_double_string(char c);
//tokenize.c
char		**add_token(char **tokens, char *input, int start, int *i);
char		**refine_tokens(char **tokens, int i, char **envp);
char		**tokenize(char *input, int i);

//PIPE
//pip_utils.c
int			free_all(char **str_arr);
void		throw_error(char *message, int exit_status, int error_number);
char		**parse_cmd(int argc, char *argv[]);
char		*validate_path(char **path_arr, char *cmd);
char		*find_path(char *cmd);
void		execute_cmd(char **cmd);
//pipe.c
int			my_pipe(int argc, char *argv[], char *envp[]);

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