/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jason <jason@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:28:30 by mkhaing           #+#    #+#             */
/*   Updated: 2024/05/15 22:02:56 by jason            ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>

# define DEBUG_MODE 1

typedef struct s_bjsh
{
	int	status;
	int in;// for stdin
	int out;// for stdout
}		t_bjsh;

void	bjsh_loop(t_bjsh *bjsh);

// builtin cmds
int		bjsh_pwd(void);
int		bjsh_cd(char *path);
int		bjsh_help(char **args);
int		bjsh_exit(void);

// exec
int		bjsh_exec(char **args);

// extras
int		bjsh_show_error(char *msg);
#endif // MINISHELL_H
