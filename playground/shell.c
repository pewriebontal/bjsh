#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_token
{
    char                *str;
    int                 type;
    struct s_token      *prev;
    struct s_token      *next;
}                       t_token;

// Function prototypes
void execute_command(t_token *token);
void handle_pipe(t_token **token);
void handle_redirection(t_token **token);

void execute_command(t_token *token)
{
    char *argv[100];
    int argc = 0;

    while (token && token->type != PIPE && token->type < REDIRECT_OUT)
    {
        argv[argc++] = token->str;
        token = token->next;
    }
    argv[argc] = NULL;

    if (argv[0] != NULL)
    {
        if (fork() == 0)
        {
            // Handle redirections before executing
            handle_redirection(&token);
            execvp(argv[0], argv);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
        }
    }
}

void handle_pipe(t_token **token)
{
    int pipefd[2];
    pid_t pid;

    pipe(pipefd);
    if ((pid = fork()) == 0)
    {
        // Child process for the first part of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execute_command(*token);
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        wait(NULL);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        *token = (*token)->next;
    }
}

void handle_redirection(t_token **token)
{
    int fd;
    while (*token && (*token)->type >= REDIRECT_OUT)
    {
        if ((*token)->type == REDIRECT_OUT)
        {
            fd = open((*token)->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if ((*token)->type == REDIRECT_OUT_APPEND)
        {
            fd = open((*token)->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if ((*token)->type == REDIRECT_IN)
        {
            fd = open((*token)->next->str, O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        *token = (*token)->next->next;
    }
}

int main()
{
    // Simulate a token chain (You should build this from your parser)
    t_token tokens[] = {
        {"ls", -1, NULL, &tokens[1]},
        {"-la", -1, &tokens[0], &tokens[2]},
        {"wc", -1, &tokens[1], &tokens[3]},
        {"|", 666, &tokens[2], &tokens[4]},
        {"cat", -1, &tokens[3], &tokens[5]},
        {"-e", -1, &tokens[4], &tokens[6]},
        {"<<<", 555, &tokens[5], &tokens[7]},
        {"hello.txt", -1, &tokens[6], &tokens[8]},
        {"|", 666, &tokens[7], &tokens[9]},
        {"wc", -1, &tokens[8], &tokens[10]},
        {"-l", -1, &tokens[9], &tokens[11]},
        {"", 0, &tokens[10], NULL}
    };

    t_token *token = tokens;
    while (token)
    {
        if (token->type == PIPE)
        {
            handle_pipe(&token);
        }
        else if (token->type >= REDIRECT_OUT)
        {
            handle_redirection(&token);
        }
        else
        {
            execute_command(token);
            while (token && token->type < PIPE)
                token = token->next;
        }
    }

    return 0;
}

