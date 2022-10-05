# Minishell
![42_logo](https://user-images.githubusercontent.com/76601093/194141661-6372bc11-7d3a-4cae-ab18-4ed732cddc9a.jpg)

As beautiful as shell

## Introduction

The aim of the project is to recreate a linux terminal from scratch using C programmming language.
In this very simple version, some of the features of a shell were implemented as environment variables, pipes and redirections.
The main goal is to have a good understanding of processes and learn more about file descriptors.

Development team:
  - [Fred](https://github.com/coderMeira/Minishell/commits?author=co) - fmeira       
  - [Arsénio](https://github.com/RealMadnessWorld) - jarsenio
## Usage
### Build Instructions

	$ git clone https://github.com/coderMeira/Minishell/
	$ cd Minishell
	$ make
	$ ./minishell

### Run the program

	$ ./minishell

## Functions

- Show a prompt when waiting for a new command
- Navigate through command history using up ```↑``` and down ```↓``` arrows
- Builtin implementation:
	- -```echo``` (with flag ```-n```)
	- -```cd``` (absolute and relative path)
	- -```pwd```
	- -```export```
	- -```unset```
	- -```env```
	- -```exit```
- Environment variables (```$``` followed by characters)
- Simple quotes ```'``` and double quotes ```"``` should work like in bash
- Pipes ```|```
- Redirections ```<```, ```>```, ```>>```
- ```ctrl-C```, ```ctrl-D``` and ```ctrl-\``` signals must be handled
- ```$?``` it should work like in bash.
