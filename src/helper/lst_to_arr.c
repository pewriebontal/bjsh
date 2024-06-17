/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:38:36 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/17 22:26:48 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**lst_to_arr(t_token *token)
{
	char	**arr;
	int		i;

	i = 0;
	arr = (char *)malloc(sizeof(char *) * (420) * 69);
	while (token)
	{
		arr[i] = ft_strdup(token->str);
		token = token->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	debug_print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != '\0')
	{
		ft_printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
}
