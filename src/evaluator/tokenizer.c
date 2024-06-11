/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhaing <0x@bontal.net>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:02:10 by mkhaing           #+#    #+#             */
/*   Updated: 2024/06/12 01:58:55 by mkhaing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Helper function to create a new token node
// this one is just for token_split_redirect
t_token *create_token_node(const char *str, int type)
{
    t_token *new = (t_token *)malloc(sizeof(t_token));
    new->str = strdup(str);
    new->type = type;
    new->executed = 0;
    new->prev = NULL;
    new->next = NULL;
    return new;
}


t_token *split_token(t_token *token, char *pos, const char *redir, int redir_type)
{
    if (pos != token->str) // Redirection is not at the beginning
    {
        char *before = strndup(token->str, pos - token->str);
        char *after = ft_strdup(pos + strlen(redir));

        t_token *before_token = create_token_node(before, 0);
        t_token *redirect_token = create_token_node(redir, redir_type);
        t_token *after_token = create_token_node(after, 0);

        before_token->next = redirect_token;
        redirect_token->prev = before_token;
        redirect_token->next = after_token;
        after_token->prev = redirect_token;
        after_token->next = token->next;

        if (token->next)
            token->next->prev = after_token;

        if (token->prev)
            token->prev->next = before_token;
        else
            token = before_token; // Update head if it was the first token

        before_token->prev = token->prev;

        free(token->str);
        free(token);
        free(before);
        free(after);

        return after_token;
    }
    else // Redirection is at the beginning
    {
        t_token *redirect_token = create_token_node(redir, redir_type);
        char *after = ft_strdup(pos + strlen(redir));

        free(token->str);
        token->str = after;

        redirect_token->next = token;
        redirect_token->prev = token->prev;
        if (token->prev)
            token->prev->next = redirect_token;
        token->prev = redirect_token;

        if (token == token)
            token = redirect_token; // Update head if it was the first token

        return token->next;
    }
}


// iterate through a token chain if found a special character
// inside the token, split the token into two token nodes
// and insert a new token node with the special character
// between the two token nodes and return the head of the
// token chain.

// example: "[echo] [>>hello.txt]" -> "[echo] [>>] [hello.txt]"
// return : "[echo] [>>] [hello.txt]"

// currently only for >> and <<

// Split the token and insert new token nodes as necessary


//
t_token *token_split_redirect(t_token *token)
{
    t_token *tmp = token;

    while (tmp)
    {
        char *pos;

        if ((pos = strstr(tmp->str, "<<<")) != NULL)
        {
            tmp = split_token(tmp, pos, "<<<", REDIRECT_HERE_STRING);
        }
        else if ((pos = strstr(tmp->str, "<<")) != NULL)
        {
            tmp = split_token(tmp, pos, "<<", REDIRECT_IN_HERE);
        }
        else if ((pos = strstr(tmp->str, ">>")) != NULL)
        {
            tmp = split_token(tmp, pos, ">>", REDIRECT_OUT_APPEND);
        }
        else if ((pos = strstr(tmp->str, ">")) != NULL)
        {
            tmp = split_token(tmp, pos, ">", REDIRECT_OUT);
        }
        else if ((pos = strstr(tmp->str, "<")) != NULL)
        {
            tmp = split_token(tmp, pos, "<", REDIRECT_IN);
        }
        else
        {
            tmp = tmp->next;
        }
    }
    return token;
}
