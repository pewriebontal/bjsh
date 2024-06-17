/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rejoin_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:14:48 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/14 02:53:45 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_rejoin_arr(char **arr)
{
	if (arr == NULL)
		return (NULL);

	// Calculate the total length required for the new string
	size_t total_length = 0;
	for (int i = 0; arr[i] != NULL; i++)
	{
		total_length += ft_strlen(arr[i]);
	}

	// Allocate memory for the new string, plus one for the null terminator
	char *result = (char *)malloc(total_length + 1);
	if (result == NULL)
		return (NULL);

	// Copy each string into the result string
	result[0] = '\0'; // Initialize the result string
	for (int i = 0; arr[i] != NULL; i++)
	{
		strcat(result, arr[i]);
	}

	return (result);
}