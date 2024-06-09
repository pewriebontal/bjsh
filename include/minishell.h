/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:28:30 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/05 00:23:15 by mkhaing          ###   ########.fr       */
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
# define SHELL_PROMPT "🍦bjsh👍 "

// token type
# define PIPE 0
# define RDIR_R 1
# define RDIR_RR 2
# define RDIR_L 3
# define END 4

# ifndef SHELL_BUILD_DATE
#  define SHELL_BUILD_DATE "unknown"
# endif

typedef struct s_token
{
	char				*str;
	struct s_avg		*prev;
	struct s_avg		*next;
}				t_token;

typedef struct s_env
{
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_bjsh
{
	t_token				*token;
	// t_env				*env;
	char				**env;
	char				*argv;
	int					status;
	int st_in;  // for stdin
	int st_out; // for stdout
}						t_bjsh;

typedef struct s_bjsh_hist
{
	char				*cmd;
	struct s_bjsh_hist	*next;
	struct s_bjsh_hist	*prev;
}						t_bjsh_hist;

void					bjsh_loop(t_bjsh *bjsh);

// builtin cmds
int						bjsh_pwd(void);
int						bjsh_cd(char *path);
int						bjsh_help(char **args);
int						bjsh_exit(void);

// env.c
int						init_env(t_bjsh *bjsh, char **env_avg);
void					show_env(t_bjsh *bjsh);

// exec
int						bjsh_exec(char **args, t_bjsh *bjsh);

//pipe.c
void    check_perr(char *a, int p);
void    execve_pipe(t_bjsh *bjsh);

// extras
int						bjsh_show_error(char *msg);
void					display_error_msg(char *msg);

// signal_handaler
void					handle_signal(int sig);
void					handle_eof(void);

// avg.c
t_token	*new_token(char *cmd);
t_token	*update_token(t_token *old_cmd, t_token *new_cmd);
void    print_token(t_token *cmd);
void	free_token(t_token **cmd);
int		set_token_list(t_bjsh *bjsh);


#endif // MINISHELL_H
