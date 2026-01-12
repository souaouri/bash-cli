# bash-cli

A lightweight Unix shell implementation written in C, mimicking the behavior of bash with essential shell functionalities.

## Overview

Minishell is a command-line interpreter that provides a subset of bash features, including command execution, built-in commands, input/output redirection, pipes, and environment variable handling.

## Features

### Core Functionality
- Interactive command prompt
- Command execution with PATH resolution
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)
- Command history
- Environment variable expansion
- Quote handling (single and double quotes)

### Built-in Commands
- `echo` - Display text with option -n
- `cd` - Change directory with relative/absolute paths
- `pwd` - Print current working directory
- `export` - Set environment variables
- `unset` - Remove environment variables
- `env` - Display environment variables
- `exit` - Exit the shell

### Advanced Features
- Input/output redirection (`<`, `>`, `>>`)
- Pipes (`|`) for command chaining
- Heredoc (`<<`) functionality
- Wildcard expansion
- Syntax error detection and reporting

## Project Structure

```
.
├── main.c                    # Entry point and main shell loop
├── minishell.h              # Header file with structures and function declarations
├── addresses_collector.c    # Memory management utilities
├── signals.c               # Signal handling implementation
├── Makefile               # Build configuration
├── execution/             # Command execution module
│   ├── builtins/         # Built-in command implementations
│   ├── builtins_utils/   # Utilities for built-in commands
│   ├── src/              # Core execution logic
│   └── utils/            # Execution utilities
├── parsing/              # Input parsing and tokenization
│   ├── lexer_list.c     # Lexical analysis
│   ├── tokenizer.c      # Token generation
│   ├── syntax_error.c   # Syntax validation
│   ├── quotes_spaces.c  # Quote and space handling
│   ├── expanding/       # Variable expansion
│   └── parser/          # Command parsing
└── test_files/          # Test files for validation
```

## Building and Running

### Prerequisites
- GCC compiler
- Make build system
- Unix-like operating system (Linux, macOS)

### Compilation
```bash
make
```

### Running
```bash
./minishell
```

### Cleaning
```bash
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild from scratch
```

## Usage Examples

```bash
# Basic commands
$ echo "Hello, World!"
Hello, World!

$ pwd
/Users/username/minishell

$ cd /tmp
$ pwd
/tmp

# Environment variables
$ export MY_VAR="test value"
$ echo $MY_VAR
test value

# Pipes and redirection
$ ls -l | grep minishell
$ echo "output" > file.txt
$ cat < file.txt

# Built-in commands
$ env
$ exit
```

## Testing

The project includes test files in the `test_files/` directory for validation:
- `empty` - Empty file for testing
- `infile` - Sample input file
- `invalid_permission` - File with restricted permissions
- And more...

You can also use the included Python tester:
```bash
python3 tester.py
```

## Memory Management

The project implements careful memory management with:
- Address collection system for tracking allocations
- Proper cleanup on exit and error conditions
- Memory leak prevention

## Error Handling

- Syntax error detection and reporting
- Signal handling for graceful interruption
- Proper error codes and messages
- Invalid permission handling

## Contributing

1. Follow the existing code style and structure
2. Test your changes thoroughly
3. Ensure no memory leaks
4. Update documentation as needed

## License

This project is part of the 42 School curriculum.