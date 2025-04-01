# Minishell

**Minishell** is a simple Unix shell implementation, developed as part of the 42 curriculum. It mimics basic shell functionalities, including executing commands, handling pipes, redirects, and managing environment variables. The project focuses on system calls, process management, and string manipulation in C.

## Features

- ✅ **Command Execution**  
  - Executes commands entered by the user.
  
- ✅ **Pipes**  
  - Supports piping between commands.
  
- ✅ **Redirections**  
  - Handles input and output redirections (`<`, `>`, `>>`).
  
- ✅ **Environment Variables**  
  - Supports managing and using environment variables (`$VAR`).
  
- ✅ **Command History**  
  - Tracks and allows accessing previous commands entered.

## Technologies Used

- 💻 **Language:** C  
- 🖥️ **System Calls:** `fork()`, `exec()`, `wait()`, `pipe()`, `dup2()`  
- 🧑‍💻 **Additional Technologies:** String manipulation, Process management

## Goals

The goal of **Minishell** is to build a functional Unix shell that mimics the behavior of a real shell, while focusing on system-level programming, process control, and user input handling in C.

## How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/erikgonk/minishell.git && cd minishell
2. Execute it:
   ```bash
   make && ./minishell
