/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:43:56 by mkhaing           #+#    #+#             */
/*   Updated: 2024/05/24 18:58:17 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	display_prompt_msg(void)
{
	ft_putstr_fd("🍦bjsh👍 ", 1);
}

void	display_error_msg(char *msg)
{
	ft_putstr_fd("🍦bjsh👎 ", 1);
	ft_putstr_fd(msg, 1);
}

void	display_info_msg(char *msg)
{
	ft_putstr_fd("🍦bjsh👌 ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
}

void	display_warning_msg(char *msg)
{
	ft_putstr_fd("🍦bjsh👀 ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
}

void	display_success_msg(char *msg)
{
	ft_putstr_fd("🍦bjsh👏 ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
}
