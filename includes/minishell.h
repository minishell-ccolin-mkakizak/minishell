/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:19:33 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/24 12:38:53 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//==========================================================================//
//									LIBRARIES								//
//==========================================================================//
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

//==========================================================================//
//									STRUCTURES								//
//==========================================================================//

//=========================>> COMMAND LINKED LIST <<========================//
typedef struct s_command
{
	char				*command;
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

//======================>> ENVIRONMENT VARIABLE LIST <<=====================//
typedef struct s_env_list
{
	char				*name;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

//============================>> COMMAND TABLE <<===========================//
typedef struct s_command_table
{
	t_command			*head;
	int					exit_status;
	int					exit_shell;
	t_env_list			*envp;
}						t_cmnd_tbl;

//================================>> TOKEN <<===============================//
typedef struct s_token
{
	char				*token;
	int					type;
	struct s_token		*next;
}						t_token;

//=============================>> LEXER DATA <<=============================//
typedef struct s_lx_dt
{
	int					next_token_type;
	int					previous_token_type;
	int					expecting_command;
	t_env_list			*envp;
}						t_lx_dt;

//===========================>> FILE DESCRIPTERS <<=========================//
typedef struct s_fd
{
	int					stdin_backup;
	int					stdout_backup;
	int					pipe_fd[2];
}						t_fd;

//==========================================================================//
//									MACROS									//
//==========================================================================//

//===============================>> PARSER <<===============================//
# define STRING_TYPE 100
# define COMMAND 101
# define SINGLE_QUOTE 104
# define DOUBLE_QUOTE 105
# define INPUT_TYPE 106
# define OUTPUT_TYPE 107
# define HEREDOC 108
# define APPEND 109
# define PIPE 110
# define ENVP 111
# define PARSING_ERROR 112

//================================>> PROMPT <<==============================//
# ifdef __APPLE__
#  define IS_LINUX 0
# endif
# ifndef IS_LINUX
#  define IS_LINUX 1
# endif
# define HSTNM_MAC "/Library/Preferences/SystemConfiguration/preferences.plist"
# define HOSTNAME_LINUX "/etc/hostname"

//========================>> INPUT/OUTPUT PIPE FDS <<=======================//
# define INPUT 0
# define OUTPUT 1

//=========================>> PRINT COMMAND TABLE <<========================//
# ifndef TABLE_DEBUG
#  define TABLE_DEBUG 0
# endif

//==========================================================================//
//							DEVELOPMENT TOOLS FUNCTIONS						//
//==========================================================================//

//=========================>> PRINT_COMMAND_TABLE.C <<======================//
void					print_command(t_command *cmd);
void					print_command_args(t_command *cmd);
void					print_command_details(t_command *cmd);
void					print_cmnd_tbl(t_cmnd_tbl *table);
void					print_commands(t_cmnd_tbl *table);

//============================>> PARSING_DEBUG.C <<=========================//
void					print_envp(char **envp);
const char				*gettokentypebame(int type);
void					print_tokens(t_token *token);

//==========================================================================//
//								PARSING FUNCTIONS							//
//==========================================================================//

//============================>> CONTINUE_INPUT.C <<========================//
char					*continue_input(char *input, char *str);
void					go_to_end_of_quotes(char *input, int *j, char c);
char					*continue_input_if_lst_tok_is_pipe(char *input, int i);

//==========================>> EXPEND_ENVPS_COMMAND.C <<====================//
char					*remove_quotes(char *command, int i, int j,
							int *is_quoted_string);
int						quoteless_strlen(char *str, int i, int j);
char					*expend_command_envps(char *command, t_env_list *envp,
							int *is_quoted_string);

//==============================>> EXPEND_ENVPS.C <<========================//
char					*expend_envp(char *str, t_env_list *envp);
char					*replace_substring_with_envp(char *str, int start,
							int end, t_env_list *envp);
char					*find_envps(char *str, t_env_list *envp,
							int is_command);
void					expend_envps(t_token *token, t_env_list *envp);

//============================>> FREE_PARSER_DATA.C <<======================//
void					free_tokens(t_token *token);
void					free_parser_data(t_token *token, t_lx_dt *lx_dt);

//================================>> LEXER.C <<=============================//
void					init_lexer(t_token **token, t_lx_dt *lx_dt, char *input,
							t_cmnd_tbl *c);
int						is_command_token(t_lx_dt *lx_dt);
int						tokenize(t_token *token, char *input, t_lx_dt *lx_dt,
							int i);
int						next_token(t_token *token, char *input, t_lx_dt *lx_dt,
							int i);
int						next_token_type(char *input, int i);

//===============================>> PARSING.C <<============================//
int						parse(char *input, t_cmnd_tbl *command_table);

//============================>> SYNTAX_CHECK.C <<==========================//
int						is_previous_tok_operator_except_pipe(t_lx_dt *lx_dt);
int						is_current_tok_operator_except_pipe(t_token *token);
int						is_arg(int type);
int						syntax_check(t_token *token, t_lx_dt *lx_dt,
							int is_last);

//============================>> TOKEN_HANDLERS.C <<========================//
int						quote_token(t_token *token, char *input, t_lx_dt *lx_dt,
							int i);
int						envp_token(t_token *token, char *input, t_lx_dt *lx_dt,
							int i);
int						dbl_char_opr_tok(t_token *token, char *input,
							t_lx_dt *lx_dt, int i);
int						sngl_char_opr_tok(t_token *token, char *input,
							t_lx_dt *lx_dt, int i);
int						string_token(t_token *token, char *input,
							t_lx_dt *lx_dt, int i);

//===========================>> TOKEN_HANDLERS_2.C <<=======================//
int						command_token(t_token *token, char *input,
							t_lx_dt *lx_dt, int i);

//===============================>> UTILITIES.C <<==========================//
int						is_valid_key_char(char c, int is_first_char);
int						skip_spaces_tabs(char *input, int i);
int						is_delimiter(char *input, int i);
int						set_quotes_flags(char c, int *in_squote, int *in_dquote);

//==========================================================================//
//							COMMAND TABLE FUNCTIONS							//
//==========================================================================//

//===========================>> BUILT_IN_CHECK.C <<=========================//
int						is_specific_builtin(t_command *command,
							const char *builtin);
int						is_built_in(t_command *command);

//=========================>> COMMAND_TABLE_BUILD.C <<======================//
void					process_tokens(t_token **token, t_command *command);
void					build_command_table(t_token *token,
							t_cmnd_tbl *command_table);
t_token					*add_command(t_token *token, t_command *command);
t_token					*add_operator(t_token *token, t_command *command);
t_token					*add_args(t_token *token, t_command *command, int i);

//==========================>> COMMAND_TABLE_INIT.C <<======================//
void					init_command_table(t_cmnd_tbl **command_table,
							char *envp[]);
void					init_command(t_command *command, int is_pipe);
t_command				*init_new_command(int is_pipe);

//===========================>> OPERATOR_HANDLERS.C <<======================//
void					realloc_array(char ***array, int i);
t_token					*handle_input_operator(t_token *token,
							t_command *command);
t_token					*handle_output_append_operator(t_token *token,
							t_command *command);
t_token					*handle_heredoc_operator(t_token *token,
							t_command *command);

//==========================================================================//
//								PROMPT FUNCTIONS							//
//==========================================================================//

//===========================>> PROMPT_BUILDER.C <<=========================//
void					build_prompt2(char *prompt, int total_len, char *hstam,
							char *cur_dir);
char					*build_prompt(char *hostname);

//============================>> PROMPT_LINUX.C <<==========================//
char					*get_linux_hostname(void);
char					*get_current_dir(const char *path, char delimiter);
char					*get_hostname(void);
char					*get_prompt_suffix(void);
char					*colon_or_space(void);

//=============================>> PROMPT_MAC.C <<===========================//
char					*get_dir_mac(const char *path, char delimiter);
char					*extract_mac_hostname(int fd);
char					*parse_mac_hostname(char *line);

//==========================================================================//
//								EXECUTION FUCNTIONS							//
//==========================================================================//

//==========================================================================//
//										ENV									//
//==========================================================================//

//================================-->> INIT.C <<============================//
t_env_list				*init_env(char *envp[]);
void					print_env_list(t_env_list *head);
void					free_env_list(t_env_list *head);
t_env_list				*create_node(char *env);
void					free_env_node(t_env_list *node);
char					*get_env_var(t_env_list *envs, char *name);

//==========================================================================//
//							BUILT-IN COMMANDS FUNCTIONS						//
//==========================================================================//

//============================>> BUILT_IN_CMDS.C <<=========================//
int						built_in_cmds(t_command *cmd, t_cmnd_tbl *table,
							int is_child);

//================================>> EXE_*.C <<==============================//
void					exe_cd(t_command *cmd, t_cmnd_tbl *table);
void					exe_unset(t_command *cmd, t_cmnd_tbl *table);
void					exe_pwd(t_command *cmd, t_cmnd_tbl *table);
void					exe_env(t_command *cmd, t_cmnd_tbl *table);
void					exe_export(t_command *cmd, t_cmnd_tbl *table);
void					exe_exit(t_command *cmd, t_cmnd_tbl *table);

//==============================>> EXE_UTILS.C <<===========================//
int						is_match(char *str1, char *str2);
int						get_array_len(char **array);
int						print_str_arr(char **arr, int len);

//==========================================================================//
//							EXECUTION FUNCTIONS								//
//==========================================================================//

//==============================>> EXECUTION.C <<===========================//
// int	main_execution(char *envp[]);

//==============================>> PIPELINE.C <<============================//
int						pipeline(t_cmnd_tbl *table, char *envp[]);

//==============================>> HERE_DOC.C <<============================//
int						check_for_dilimiter(t_command *cmd, char *input);
int						handle_heredoc(t_command *cmd);

//===========================>> EXECUTE_COMMAND.C <<========================//
char					*validate_path(char **path_arr, char *cmd);
char					*find_path(char *cmd, t_env_list *table);
int						execute_cmd(t_command *cmd, t_cmnd_tbl *table,
							int is_child, char *envp[]);

//===========================>> PIPELINE_UTILS.C <<=========================//
void					throw_error(char *message, int exit_status,
							int error_number);
pid_t					safe_fork(void);
void					init_fd(t_fd *fd);
void					restore_fd(t_fd *fd);
void					init_pipe(t_fd *fd);
int						has_pipe(t_command *head);

#endif
