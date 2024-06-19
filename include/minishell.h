/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:28:30 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/20 02:21:20 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H

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
# include <sys/types.h>
# include <sys/wait.h>

# define DEBUG_MODE 1

# define SHELL_SHORT_NAME "bjsh"
# define SHELL_LONG_NAME "Bon & Jason's shell"
# define SHELL_VERSION "development build"
//# define SHELL_PROMPT "🍦bjsh👍 "
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

#define MAX_ARGS 100

# ifndef SHELL_HISTORY_FILE
#  define SHELL_HISTORY_FILE ".bjsh_history"
# endif

# ifndef SHELL_BUILD_DATE
#  define SHELL_BUILD_DATE "unknown"
# endif

typedef struct s_token
{
	char				*str;
	int					type;
	int					executed;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

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
	int std_in;  // for stdin
	int std_out; // for stdout
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

// builtin cmds
int						bjsh_pwd(void);
int						bjsh_cd(char *path);
int						bjsh_help(char **args);
int						bjsh_exit(t_bjsh *bjsh, char *args);

// env.c
int						init_env(t_bjsh *bjsh, char **env_avg);
void					show_env(t_bjsh *bjsh);

// exec
int						bjsh_exec(char **args, t_bjsh *bjsh);

// pipe.c
void					check_perr(char *a, int p);
void					execve_pipe(t_bjsh *bjsh);

// extras
int						bjsh_show_error(char *msg);
void					display_error_msg(char *msg);

// signal_handaler
void					handle_signal(int sig);
void					handle_eof(void);

// avg.c
t_token					*new_token(char *cmd);
t_token					*update_token(t_token *old_cmd, t_token *new_cmd);
char					*expand_env(char *arr);
void					print_token(t_token *cmd);
void					free_token(t_token **cmd);
int						set_token_list(t_bjsh *bjsh, char *arr);

//
// Function prototypes
void					execute_command(t_token *tokens, char **envp);
void					handle_redirection(t_token **tokens);
void					handle_pipes(t_token *tokens, char **envp);
char					*find_executable(const char *command, char **envp);
int						check_builtin(char *command);
void					execute_builtin(char **args);

// tokenizer
t_token					*token_split_redirect(t_token *token);
t_token					*remove_quotes_from_token(t_token *token);

// helpers/arr_to_list.c
t_token					*array_to_list(char **arr);
void					clear_list(t_token *token);
void					debug_print_list(t_token *token);

// helpers/ft_rejion_arr.c
char					*ft_rejoin_arr(char **arr);

// helpers/lst_to_arr.c
char					**lst_to_arr(t_token *token);
void					debug_print_arr(char **arr);

#endif // MINISHELL_H
