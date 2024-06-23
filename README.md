# BJSH - Bon & Jason's Shell

## The birth of Bon & Jason's Shell (BJSH)!

One day, Bon and Jason, two friends with a shared love for coding and memes, thought it would be funny to create a programming language called Bon and Jason Programming Language with the file extension .bj. However, after they found the Minishell project at 42, they decided to work together on that instead. They created their own shell and named it 'Bon and Jason's Shell', or **BJSH** for short.

## Introduction

BJSH (Bon & Jason's Shell) is a custom shell written in C, designed to provide an interactive command-line interface similar to Unix-like shells. It supports various standard shell functionalities including command execution, piping, redirections, environment variables, and built-in commands.

## Features

- Command prompt and history
- Executable search in system paths
- Input/output redirections (>, >>, <)
- Here documents (<<)
- Pipes (|)
- Environment variable management
- Built-in commands for common tasks (e.g., cd, echo, exit)
- Signal handling for interactive mode
- Quoting and escaping mechanism for handling complex inputs

## Getting Started

### Prerequisites

- GCC compiler
- GNU Make
- Readline library
- BYAMC

### Installation

To install BJSH, follow these steps:

Clone the repository:

```sh
git clone https://github.com/pewriebontal/bjsh.git --recursive
cd bjsh
```

Compile the project:

```sh
make
```

Run the shell:

```sh
./bjsh
```

### Usage

Once BJSH is running, you can use it similarly to other Unix-like shells. Here are some example commands:

```sh
# Running a simple command
ls -la

# Using pipes
ls -la | grep .c | wc -l

# Redirections
echo "Hello, World!" > hello.txt
cat < hello.txt

# Environment variables
echo $PATH

# Built-in commands
cd /path/to/directory
echo "This is BJSH"
exit
```
