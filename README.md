# 42 Cursus

## Pipex 🐚
The pipex project challenges you to emulate the behavior of the Unix shell command pipex, allowing users to redirect the output of one command as the input to another.  
Low-level programming concepts and a deep understanding of Unix system calls; handling file descriptors, processes, pipes, and command executions.  

## How to use:

1. Clone the repository:
```c
git clone https://github.com/aldferna/Pipex.git
```
2. Compile the project:
```c
make
```
3. Compile the bonus part:
```c
make bonus
```
4. Run the program with the following syntax:
```c
./pipex infile cmd1 cmd2 outfile
```

🗒 **Example**
```c
./pipex input.txt "grep keyword" "sort -r" output.txt
```
To test the first part of the bonus, use three or more commands:
```c
./pipex input.txt "grep keyword" "sort -r" "wc -l" output.txt
```
