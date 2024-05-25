/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:28:30 by mkhaing           #+#    #+#             */
/*   Updated: 2024/05/25 18:17:26 by mkhaing          ###   ########.fr       */
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

# ifndef SHELL_BUILD_DATE
#  define SHELL_BUILD_DATE "unknown"
# endif

typedef struct s_token
{
	int					pipe;
	int					redir_right;
	int					redir_left;
	int					end;
}						t_token;
typedef struct s_bjsh
{
	t_token				*token;
	char				*argv;
	int					status;
	int st_in;  // for stdin
	int st_out; // for stdout
}						t_bjsh;

typedef struct s_cmd
{
	int					type;
	int					input;
	int					output;
}						t_cmd;

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

// exec
int						bjsh_exec(char **args);

// extras
int						bjsh_show_error(char *msg);

// signal_handaler
void					handle_signal(int sig);

// token.c
t_bjsh					*save_token(t_bjsh *bjsh);
#endif // MINISHELL_H
