/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:45:07 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/20 19:37:35 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
t_token *create_token(char *str, int type)
{
    t_token *new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->str = strdup(str);
    new_token->type = type;
    new_token->executed = 0;
    new_token->prev = NULL;
    new_token->next = NULL;
    return new_token;
}

void insert_after(t_token *current, t_token *new_token)
{
    if (!current || !new_token)
        return;
    new_token->next = current->next;
    new_token->prev = current;
    if (current->next)
        current->next->prev = new_token;
    current->next = new_token;
}

void split_token(t_token *token)
{
    if (!token || !token->str)
        return;

    char *str = token->str;
    size_t len = strlen(str);

    // Check for different redirection patterns
    char *pos = NULL;
    if ((pos = strstr(str, ">>")) || (pos = strstr(str, "<<")) || (pos = strchr(str, '>')) || (pos = strchr(str, '<')))
    {
        // Calculate the lengths of the two parts
        size_t prefix_len = pos - str;
        size_t suffix_len = len - prefix_len - ((pos[1] == '>' || pos[1] == '<') ? 2 : 1);

        // Create the redirection token
        char redirection[3] = {0};
        if (pos[1] == '>' || pos[1] == '<')
        {
            redirection[0] = pos[0];
            redirection[1] = pos[1];
        }
        else
        {
            redirection[0] = pos[0];
        }
        t_token *redirection_token = create_token(redirection, token->type);

        // Create the suffix token
        char *suffix = pos + ((pos[1] == '>' || pos[1] == '<') ? 2 : 1);
        t_token *suffix_token = create_token(suffix, token->type);

        // Update the current token to the prefix
        if (prefix_len > 0)
        {
            char *prefix = strndup(str, prefix_len);
            free(token->str);
            token->str = prefix;
        }
        else
        {
            // If there's no prefix, move redirection token to the current position
            token->str = strdup(redirection);
            free(redirection_token->str);
            redirection_token = token;
        }

        // Insert the new tokens into the linked list
        if (redirection_token != token)
            insert_after(token, redirection_token);
        insert_after(redirection_token, suffix_token);
    }
}

void split_token_chain_redirect(t_token *token)
{
    t_token *current = token;
    while (current)
    {
        t_token *next = current->next;
        split_token(current);
        current = next;
    }
}