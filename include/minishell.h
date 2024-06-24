/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:28:30 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/24 21:17:16 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <byamc/bool.h>
# include <byamc/byamc.h>
# include <byamc/colors.h>
# include <byamc/ft_printf.h>
# include <byamc/gnl.h>
# include <byamc/gzdef.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define DEBUG_MODE 1

# define SHELL_SHORT_NAME "bjsh"
# define SHELL_LONG_NAME "Bon & Jason's shell"
# define SHELL_VERSION "development build"
// # define SHELL_PROMPT "🍦bjsh👍 "
# define SHELL_PROMPT "🍒 ❯ "

// token type
# define REDIRECT_OUT 111         // >
# define REDIRECT_OUT_APPEND 222  // >>
# define REDIRECT_IN 333          // <
# define REDIRECT_IN_HERE 444     // <<
# define REDIRECT_HERE_STRING 555 // <<<
# define PIPE 666                 // |
# define COMMAND 777              //
# define FILE 888                 //

# define BUGGI_BAKA 69420 // cd, exit  (kill the parent)
# define SUSSY_BAKA 42069 // the rest of the builtins (kill the child)

# define MAX_ARGS 100

# ifndef SHELL_HISTORY_FILE
#  define SHELL_HISTORY_FILE ".bjsh_history"
# endif

# define BJSH_TEMP_FILE "/tmp/bjsh_temp"

# ifndef SHELL_BUILD_DATE
#  define SHELL_BUILD_DATE "unknown"
# endif

# ifndef GIT_COMMIT
#  define GIT_COMMIT "unknown"
# endif

typedef struct s_env_replacer
{
	int					in_single_quote;
	int					in_double_quote;
	char				*result;
	size_t				result_len;
}						t_env_replacer;

typedef struct s_token
{
	char				*str;
	int					type;
	int					executed;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_execution_context
{
	t_token				*current;
	int					in_fd;
	int					out_fd;
	int					fd[2];
	int					status;
	int					command_found;
	int					argc;
}						t_execution_context;

typedef struct s_redirction_data
{
	int					flags;
	char				*heredoc_file;
	int					temp_fd;
	char				buffer[1024];
	ssize_t				bytes_read;
	ssize_t				bytes_written;
}						t_redirection_data;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_bjsh
{
	t_token				*token;
	t_env				*env;
	char				**envp;
	char				*argv;
	int					status;
	int					state;
	int					last_exit_status;
}						t_bjsh;

typedef struct s_history
{
	char				*cmd;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

// main.c
void					bjsh_loop(t_bjsh *bjsh);

// bjsh/env.c
void					append_env_node(t_env **head, t_env *new_node);
t_env					*create_env_list(t_bjsh *bjsh);
void					bjsh_env_init(t_bjsh *bjsh);
void					add_back(t_env **lst, t_env *new);
t_env					*ft_envlast(t_env *lst);

// bjsh/env2.c
t_env					*create_env_node(const char *key, const char *value);
void					split_env(const char *env_str, char **key,
							char **value);
void					initialize_env_list(t_env **head, t_env **tail);
void					remove_env(t_env **env, const char *key);
int						count_env_vars(t_env *env);

// bjsh/env3.c
char					**allocate_envp(int count);
char					*create_env_string(const char *key, const char *value);
char					**convert_env_to_envp(t_env *env);
void					process_env_variable(char *env_var, t_env **head);

// bjsh/hist.c
char					*bjsh_get_history_path(void);
void					bjsh_hist_file_create(void);
int						bjsh_read_history(char *path);
int						bjsh_write_history(char *path);

// bjsh/main.c
int						init_bjsh(t_bjsh *bjsh, char *env[]);

// bjsh/message.c
void					display_error_msg(char *msg);

// bjsh/shell.c
void					bjsh_loop(t_bjsh *bjsh);
int						check_builtin(char *cmd);
int						bjsh_exec_builtin(char **args, t_bjsh *bjsh);
int						handle_export_command(t_bjsh *bjsh, char **args);
int						handle_unset_command(t_bjsh *bjsh, char **args);

// bjsh/signal_handler.c
void					handle_signal(int sig);
void					handle_eof(void);

// builtins cd.c
char					*get_path(char **args);
int						bjsh_cd(char **args, t_bjsh *bjsh);

// builtins echo.c
int						bjsh_echo(char **args);

// builtins env.c
int						bjsh_env(t_bjsh *bjsh);
t_env					*find_env(t_env *env, const char *key);
void					add_or_update_env(t_env **env, const char *key,
							const char *value);

// builtins exit.c
int						bjsh_exit(t_bjsh *bjsh, char *args);

// builtins export.c
t_env					*find_env_node(t_env *head, const char *key);
int						bjsh_export(t_bjsh *bjsh, const char *key,
							const char *value);

// builtins help.c
int						bjsh_help(char **args);

// builtins pwd.c
int						bjsh_pwd(void);

// builtins unset.c
int						bjsh_unset(t_bjsh *bjsh, const char *key);

// evaluator/envlocal.c
char					*get_path_env(void);
char					*get_env_local(char **envp, const char *key);

// evaluator/evaluate_env.c
void					fill_up_token_with_env(t_token *token, t_bjsh *bjsh);
char					*handle_quotes(char *p, t_env_replacer *replacer);
char					*handle_dollar_sign(char *p, t_env_replacer *replacer,
							t_bjsh *bjsh);
void					append_char_to_result(char c, char **result,
							size_t *result_len);
void					append_string_to_result(char *str, char **result,
							size_t *result_len);
void					replace_env_vars(char **str, t_bjsh *bjsh);

// evaluator/evaluate_quotes.c
void					replace_spaces_in_quotes(char *str);
int						count_weired_character(char *str);

// evalautor/evaluate_token.c
void					evaluate_token_chain(t_token *token, t_bjsh *bjsh);
void					remove_empty_nodes(t_token *token);

// evaluator/evaluate_type.c
void					evaluate_token_type(t_token *token);
void					update_token_type(t_token *token);

// evaluator/token_split.c
void					create_and_insert_tokens(t_token *token, char *str,
							size_t prefix_len, char *redirection);
void					process_redirection(t_token *token, char *str,
							size_t i);
void					split_token(t_token *token);
void					split_token_chain_redirect(t_token *token);
void					insert_after(t_token *current, t_token *new_token);

// evaluator/token_split2.c
t_token					*create_token(const char *str, int type);
void					handle_quotes_split_internal(char c,
							int *in_single_quote, int *in_double_quote);
int						is_redirection(char c, char next);
void					set_redirection(char *str, size_t i, char *redirection);
void					create_suffix_token(char *str, size_t prefix_len,
							char *redirection, t_token **suffix_token);

// evaluator/tokenizer.c
t_token					*bon_and_jason_tokenizer(char *command_input,
							t_bjsh *bjsh);
t_token					*remove_quotes_from_token(t_token *token);
void					remove_quotes(char *str);

// evaluator/tokenizer2.c
void					replace_special_characters(char *str,
							char special_character);
void					replace_special_characters_in_node(t_token *token,
							char special_character);
t_token					*create_token_node(const char *str, int type);
int						is_within_quotes(const char *str, const char *pos);

// executation/exec.c
void					execute_command4(char **args, char **envp);
void					initialize_execution_context(t_execution_context *context,
							t_token *head);
int						execute_single_command(char *args[],
							t_execution_context *context, t_bjsh *bjsh);
void					execute_loop(t_execution_context *context,
							t_bjsh *bjsh);
void					execute_tokens(t_token *head, t_bjsh *bjsh);

// execution/exec2.c
int						find_command(t_token *current);
void					collect_arguments(t_token **current, char *args[],
							int *argc);
void					execute_builtin_g(char *args[], t_bjsh *bjsh);
void					execute_command_or_builtin(char *args[],
							t_execution_context *context, t_bjsh *bjsh);

// execution/exehandle.c
void					handle_io_redirection(t_execution_context *context);
void					handle_child_process(char *args[],
							t_execution_context *context, t_bjsh *bjsh);
void					handle_parent_process(t_execution_context *context,
							t_bjsh *bjsh);

// execution/heredoc.c
void					read_until_limiter(t_bjsh *bjsh, int fd_input,
							int fd_output, char *limiter);
char					*read_here_doc(t_bjsh *bjsh, char *limiter);

// execution/pathfinding.c
char					*check_absolute_or_relative_path(const char *command);
char					*construct_executable_path(const char *path,
							const char *command);
char					*search_in_paths(const char *command, char *path_env);
char					*find_executable(const char *command, char **envp);

// execution/redirect_utils.c
int						open_input_file(const char *filename);
int						read_and_write_file(int file_fd,
							t_redirection_data *rd);
int						process_current_input_file(t_execution_context *context,
							t_redirection_data *rd);
int						process_input_files(t_execution_context *context,
							t_redirection_data *rd);
int						reopen_temp_file_for_reading(t_execution_context *context);

// execution/redirect.c
int						handle_redirect_out(t_execution_context *context,
							t_redirection_data *rd);
int						open_temp_file(t_redirection_data *rd);
int						handle_redirect_in(t_execution_context *context,
							t_redirection_data *rd);
int						handle_redirect_in_here(t_execution_context *context,
							t_redirection_data *rd, t_bjsh *bjsh);
int						handle_redirections(t_execution_context *context,
							t_bjsh *bjsh);

// execution/redirect2.c
int						check_invalid_redirection_sequence(t_execution_context *context);

// helpers/arr_to_list.c
t_token					*array_to_list(char **arr);
void					debug_print_list(t_token *token);
void					clear_list(t_token *token);

// helpers/ft_rejoin_arr.c
char					*ft_rejoin_arr(char **arr);

// helpers/lst_to_arr.c
char					**lst_to_arr(t_token *token);
void					debug_print_arr(char **arr);

#endif // MINISHELL_H
