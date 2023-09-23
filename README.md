<div align=center>
  <h1>
    Minishell
  </h1>
<img src="https://github.com/devicons/devicon/blob/master/icons/c/c-plain.svg" title="C" alt="C" width="60" height="60" align="right"/>

>> As beautiful as shell
</div>

---

<h2 align=center>
	Description
</h2>

The aim of the project is to recreate a linux terminal from scratch using C programmming language.<br>
In this very simple version, some of the features of a shell were implemented as environment variables, pipes and redirections.<br>
The main goal is to have a good understanding of processes and learn more about file descriptors.

<h4>
	Development team:
</h4>
  
  - [Fred](https://github.com/coderMeira) - fmeira       
  - [Arsénio](https://github.com/RealMadnessWorld) - jarsenio

---

<h2 align=center>
	How to run
</h2>

### Build Instructions

	$ git clone https://github.com/RealMadnessWorld/Minishell.git
	$ cd Minishell
	$ make
	$ ./minishell

### Run the program

	$ ./minishell

## Features

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

---

<div align="center">
	<img src="https://user-images.githubusercontent.com/76601093/193692098-d4b16956-1dab-40b8-9aae-31b254efc5ee.jpg" width=340> <img src="https://github.com/RealMadnessWorld/Minishell/assets/76601093/df2cfc5d-775e-4f21-9da0-7f010bc29c50">

</div>
