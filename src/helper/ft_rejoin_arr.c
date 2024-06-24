/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rejoin_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:14:48 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/24 18:09:45 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_rejoin_arr(char **arr)
{
	size_t	total_length;
	char	*result;
	int		i;

	if (arr == NULL)
		return (NULL);
	total_length = 0;
	i = 0;
	while (arr[i] != NULL)
	{
		total_length += ft_strlen(arr[i]);
		i++;
	}
	result = (char *)malloc(sizeof(char) * (total_length + 1));
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (arr[i] != NULL)
	{
		ft_strcat(result, arr[i]);
		i++;
	}
	return (result);
}
