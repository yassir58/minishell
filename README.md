# minishell
minishell 42 project

The existence of shells is linked to the very existence of IT.
At the time, all developers agreed that communicating with a computer using aligned
The 1/0 switches were seriously irritating.
It was only logical that they came up with the idea of creating software to communicate with a computer using interactive lines of commands in a language somewhat close to the human language.
<p>
the basic idea of minishell is that its a program that displays a prompt and takes a command line with the readline utility as a first step.
after that, i pass that line to a lexer a function that will split that line to tokens, after lexing part it comes the parser that will return a linked list of commands with is arguments separated by a pipe operator, after that we pass the linked_list that consists of execution nodes to 
the execution chain function, the execution function will handle redirections and pipes and finally will execute commands one by one.
<\p>


```bash
# Clone this repository
$ git clone https://github.com/yassir58/minishell
$ cd minishell
# Build executable
$ make

#run program
$ ./minishell
```
