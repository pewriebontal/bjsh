#include <minishell.h>

char *resolve_path(char *command) {
    char *path = getenv("PATH");
    char *token = strtok(path, ":");
    char full_path[1024];

    while (token != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
        if (access(full_path, X_OK) == 0) {
            return strdup(full_path);
        }
        token = strtok(NULL, ":");
    }
    return NULL;
}

// Function to execute a single command using execve
void execute_command4(char **args, char **envp) {
    char *path = resolve_path(args[0]);
    if (path == NULL) {
        fprintf(stderr, "Command not found: %s\n", args[0]);
        exit(EXIT_FAILURE);
    }

    if (execve(path, args, envp) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }
}

// Function to handle the execution of the t_token chain
void execute_tokens(t_token *head, char **envp) {
    t_token *current = head;
    int fd[2];
    int in_fd = 0;  // Initially, input comes from standard input

    while (current != NULL) {
        char *args[100];  // Assuming no command has more than 100 arguments
        int argc = 0;

        // Collect arguments for the current command
        while (current != NULL && current->type == -1) {
            args[argc++] = current->str;
            current = current->next;
        }
        args[argc] = NULL;  // Null-terminate the arguments array

        if (current == NULL || current->type == PIPE) {
            // If we reach a pipe or the end of the chain, execute the command
            pipe(fd);

            if (fork() == 0) {
                dup2(in_fd, 0);  // Change the input to the previous output
                if (current != NULL) {
                    dup2(fd[1], 1);  // Set the output to the pipe
                }
                close(fd[0]);
                execute_command4(args, envp);
            } else {
                wait(NULL);
                close(fd[1]);
                in_fd = fd[0];  // Save the input for the next command
                if (current != NULL) {
                    current = current->next;
                }
            }
        } else if (current->type == REDIRECT_OUT || current->type == REDIRECT_OUT_APPEND) {
            int flags = O_WRONLY | O_CREAT;
            flags |= (current->type == REDIRECT_OUT) ? O_TRUNC : O_APPEND;
            int out_fd = open(current->next->str, flags, 0644);
            if (out_fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            if (fork() == 0) {
                dup2(in_fd, 0);
                dup2(out_fd, 1);
                close(out_fd);
                execute_command4(args, envp);
            } else {
                wait(NULL);
                close(out_fd);
                if (current->next != NULL) {
                    current = current->next->next;
                }
            }
        } else if (current->type == REDIRECT_IN) {
            int in_fd = open(current->next->str, O_RDONLY);
            if (in_fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            if (fork() == 0) {
                dup2(in_fd, 0);
                close(in_fd);
                execute_command4(args, envp);
            } else {
                wait(NULL);
                close(in_fd);
                if (current->next != NULL) {
                    current = current->next->next;
                }
            }
        } else {
            // If we encounter an unsupported token type, just skip it
            current = current->next;
        }
    }
}
