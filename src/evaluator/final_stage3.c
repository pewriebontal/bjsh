/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_stage3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:24:11 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/26 17:33:20 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_special_chars(char *special_chars[], int special_types[])
{
	special_chars[0] = ">>";
	special_chars[1] = ">";
	special_chars[2] = "<<";
	special_chars[3] = "<";
	special_chars[4] = "|";
	special_chars[5] = NULL;
	special_types[0] = REDIRECT_OUT_APPEND;
	special_types[1] = REDIRECT_OUT;
	special_types[2] = REDIRECT_IN_HERE;
	special_types[3] = REDIRECT_IN;
	special_types[4] = PIPE;
}

int	process_special_chars(char **str, int *len, int i, t_token **new_token)
{
	int	special_len;

	special_len = check_special_chars(*str, new_token, i);
	if (special_len > 0)
	{
		*str += i + special_len;
		*len -= i + special_len;
		return (-1);
	}
	return (i);
}

void	add_substring_token(char *str, int length, t_token **new_token,
		int type)
{
	char	*substr;

	substr = ft_strndup(str, length);
	token_add_back(new_token, create_new_token(substr, type));
	free(substr);
}
