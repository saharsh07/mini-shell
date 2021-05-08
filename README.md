# mini-shell


Goal 

The goal of this project is to create a simple shell. In this project we will understand how processes, file descriptors, pipes, signals, execvp and bash built-ins work.

Requirements 
•	You must use Linux system calls and commands for file and for process management to implement the functionalities of your shell.
•	`system' system call should NOT be used.
•	The system calls that you need to use are fork, execvp, signal, dup, close, pipe, wait.
•	For redirection we will be using pipe command and not  >, < , >& etc.

Assumptions
•	My program can't handle background jobs or processes. So you cannot send job to background
•	My program can’t handle some built-in commands like cd, kill, history etc.
•	Ctrl+c and Ctrl+z cant be used to exit terminal.

