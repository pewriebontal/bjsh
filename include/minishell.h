/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:28:30 by mkhaing           #+#    #+#             */
/*   Updated: 2024/04/20 22:40:16 by mkhaing          ###   ########.fr       */
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

typedef struct s_bjsh
{
	int	status;
}		t_bjsh;

void	bjsh_loop(t_bjsh *bjsh);

// builtin cmds
int		bjsh_pwd(void);
int		bjsh_cd(char *path);
int		bjsh_help(char **args);
int		bjsh_exit(void);

// exec
int		bjsh_exec(char **args);

#endif // MINISHELL_H
