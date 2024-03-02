# minishell
### Intro
This project aims to create a simple shell, based on bash, in C. At this point of the cursus it's by far the largest project we have worked on and also it's the first one we must work in pairs.

### Usage
1. Download/Clone this repo

        git clone https://github.com/rscres/42minishell
2. `cd` into the project directory and run `make`

        cd 42minishell
        make
3. Run the minishell
   
       ./minishell

### About the minishell
The project had to be coded in C and we were limited on the lib functions we could use.

Some of the shell commands were implemented as builtins:
  - echo
  - exit
  - export
  - env
  - unset
  - cd
  - pwd

Echo was implemented with the -n flag and the rest without any flags. The minishell is capable of running other commands, like ls or wc, but will do it using execve().

