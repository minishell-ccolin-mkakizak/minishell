/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:19:33 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/19 16:41:29 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// command linked list
typedef struct s_command
{
	char				**args;
	char				*input_file;
	char				**output_file;
	char				*heredoc_delimiter;
	char				**append;
	int					pipe_in;
	int					pipe_out;
	int					is_built_in;
	struct s_command	*next;
}						t_command;

// enviroment_variable_list
typedef struct s_env_list
{
	char				*name;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

//command_table
typedef struct s_command_table
{
	t_command			*head;
	int					exit_status;
	int					exit_shell;
	t_env_list	*envp;
}						t_cmnd_tbl;

// file_discripters
typedef struct s_fd
{
	int					stdin_backup;
	int					stdout_backup;
	int					pipe_fd[2];
}						t_fd;

// token
typedef struct s_token
{
	char				*token;
	int					type;
	struct s_token		*next;
}						t_token;

# define STRING_TYPE 100
# define COMMAND 101
# define ARGUMENT 102
# define SINGLE_QUOTE 104
# define DOUBLE_QUOTE 105
# define INPUT_TYPE 106
# define OUTPUT_TYPE 107
# define HEREDOC 108
# define APPEND 109
# define PIPE 110
# define ENVP 111

typedef struct s_lx_dt
{
	int					next_token_type;
	int					current_token;
}						t_lx_dt;

// check if on mac or linux
# ifdef __APPLE__
#  define IS_LINUX 0
# endif
# ifndef IS_LINUX
#  define IS_LINUX 1
# endif

# define HSTNM_MAC "/Library/Preferences/SystemConfiguration/preferences.plist"
# define HOSTNAME_LINUX "/etc/hostname"

// input/output for pipe fds
# define INPUT 0
# define OUTPUT 1

# ifndef TABLE_DEBUG
#  define TABLE_DEBUG 0
# endif

// DEVELOPMENT TOOLS
// print_command_table.c
void					print_command(t_command *cmd);
void					print_command_args(t_command *cmd);
void					print_command_details(t_command *cmd);
void					print_cmnd_tbl(t_cmnd_tbl *table);
void					print_commands(t_cmnd_tbl *table);

// parsing_debug.c
void					print_envp(char **envp);
const char				*getTokenTypeName(int type);
void					print_tokens(t_token *token);


// mock_data.c
// void					free_commands(t_command *cmd);

//--------------------------PARSING FUCNTIONS-----------------------------------------//
//parsing.c
int						main_parsing(char **envp);
void					parse(char *input, t_cmnd_tbl *command_table);

// lexer.c
void					init_lexer(t_token **token, t_lx_dt *lx_dt,
							char *input);
void					tokenize(t_token *token, char *input, t_lx_dt *lx_dt,
							int i);
void					next_token(t_token *token, char *input, t_lx_dt *lx_dt,
							int i);
int						skip_spaces_tabs(char *input, int i);
int						next_token_type(char *input, int i);

// token_handlers.c
void					single_quote_token(t_token *token, char *input,
							t_lx_dt *lx_dt, int i);
void					double_quote_token(t_token *token, char *input,
							t_lx_dt *lx_dt, int i);
void					envp_token(t_token *token, char *input, t_lx_dt *lx_dt,
							int i);
void					dbl_char_opr_tok(t_token *token, char *input,
							t_lx_dt *lx_dt, int i);
void					sngl_char_opr_tok(t_token *token, char *input,
							t_lx_dt *lx_dt, int i);
void					string_token(t_token *token, char *input,
							t_lx_dt *lx_dt, int i);
// utilities.c
int						is_valid_key_char(char c, int is_first_char);
int						is_delimiter(char *input, int i);
// free_parser_data.c
void					free_tokens(t_token *token);
void					free_parser_data(t_token *token, t_lx_dt *lx_dt);

// COMMAND_TABLE
// command_table_init.c
void					init_command_table(t_cmnd_tbl **command_table, char *envp[]);
void					init_command(t_command *command, int is_pipe);
t_command				*init_new_command(int is_pipe);

// command_table_build.c
void					build_command_table(t_token *token,
							t_cmnd_tbl *command_table);
t_token					*add_args(t_token *token, t_command *command);
t_token					*add_operator(t_token *token, t_command *command);

// operators_handlers.c
t_token					*handle_input_operator(t_token *token,
							t_command *command);
t_token					*handle_output_append_operator(t_token *token,
							t_command *command);
t_token					*handle_heredoc_operator(t_token *token,
							t_command *command);

// built_in_check.c
int						is_specific_builtin(t_command *command,
							const char *builtin);
int						is_built_in(t_command *command);

// PROMPT
// build_prompt.c
char					*build_prompt(char *hostname);

// prompt_linux.c
char					*get_linux_hostname(void);
char					*get_current_dir(const char *path, char delimiter);
char					*get_hostname(void);
char					*get_prompt_suffix(void);
char					*colon_or_space(void);

// prompt_mac.c
char					*get_dir_mac(const char *path, char delimiter);
char					*extract_mac_hostname(int fd);
char					*parse_mac_hostname(char *line);



//--------------------------EXECUTIONG FUCNTIONS-----------------------------------------

// ENV
// init.c
t_env_list				*init_env(char *envp[]);
void					print_env_list(t_env_list *head);
void					free_env_list(t_env_list *head);
t_env_list				*create_node(char *env);
void					free_env_node(t_env_list *node);

// BUILT IN COMMANDS
// built_in_cmds.c
int 					built_in_cmds(t_command *cmd, t_env_list *env, int is_child);

// exe_*.c
void					exe_cd(t_command *cmd, t_env_list *env);
void					exe_unset(t_command *cmd, t_env_list *env);
void					exe_pwd(t_command *cmd, t_env_list *env);
void					exe_env(t_command *cmd, t_env_list *env);
void					exe_export(t_command *cmd, t_env_list *env);
void					exe_exit(t_command *cmd, t_env_list *env);

// exe_utils.c
int						is_match(char *str1, char *str2);

// EXECUTION
// execution.c
// int						main_execution(char *envp[]);

// pipeline.c
int						pipeline(t_cmnd_tbl *table, char *envp[]);

// here_doc.c
int						check_for_dilimiter(t_command *cmd, char *input);
int						handle_heredoc(t_command *cmd);

// execute_command.c
char					*validate_path(char **path_arr, char *cmd);
char					*find_path(char *cmd, char *envp[]);
int						execute_cmd(t_command *cmd, char *envp[], int is_child);

// pipeline_utils.c
void					throw_error(char *message, int exit_status,
							int error_number);
pid_t					safe_fork(void);
void					init_fd(t_fd *fd);
void					restore_fd(t_fd *fd);
void					init_pipe(t_fd *fd);
int 					has_pipe(t_command *head);
#endif