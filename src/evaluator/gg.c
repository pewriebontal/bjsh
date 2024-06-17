#include <minishell.h>

// Function to handle the execution of the t_token chain
void execute_tokens99(t_token *head, char **envp) {
    t_token *current = head;
    int fd[2];
    int in_fd = 0;  // Initially, input comes from standard input

    while (current != NULL) {
        char *args[100];  // Assuming no command has more than 100 arguments
        int argc = 0;
        int out_fd = -1;

        // Collect arguments for the current command
        while (current != NULL && current->type == -1) {
            args[argc++] = current->str;
            current = current->next;
        }
        args[argc] = NULL;  // Null-terminate the arguments array

        // Check for output redirection
        if (current != NULL && (current->type == REDIRECT_OUT || current->type == REDIRECT_OUT_APPEND)) {
            int flags = O_WRONLY | O_CREAT;
            flags |= (current->type == REDIRECT_OUT) ? O_TRUNC : O_APPEND;
            out_fd = open(current->next->str, flags, 0644);
            if (out_fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            current = current->next->next;
        }

        // Check if the command is a built-in
        if (check_builtin(args[0])) {
            // Handle redirection for built-ins
            if (out_fd != -1) {
                int saved_stdout = dup(STDOUT_FILENO);
                dup2(out_fd, STDOUT_FILENO);
                close(out_fd);
                bjsh_exec_builtin(args);
                dup2(saved_stdout, STDOUT_FILENO);
                close(saved_stdout);
            } else {
                bjsh_exec_builtin(args);
            }
        } else {
            if (current == NULL || current->type == PIPE) {
                // If we reach a pipe or the end of the chain, execute the command
                pipe(fd);

                if (fork() == 0) {
                    dup2(in_fd, 0);  // Change the input to the previous output
                    if (current != NULL) {
                        dup2(fd[1], 1);  // Set the output to the pipe
                    }
                    close(fd[0]);
                    if (out_fd != -1) {
                        dup2(out_fd, 1);
                        close(out_fd);
                    }
                    execute_command4(args, envp);
                } else {
                    wait(NULL);
                    close(fd[1]);
                    in_fd = fd[0];  // Save the input for the next command
                    if (current != NULL) {
                        current = current->next;
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
}