# Project 

Write a Shell in C/C++.

## Objective:

It’s easy to view yourself as “not a real programmer.” There are programs out there that everyone uses, and it’s easy to put their developers on a pedestal. Although developing large software projects isn’t easy, many times the basic idea of that software is quite simple. Implementing it yourself is a fun way to show that you have what it takes to be a real programmer.

## Description:
A shell does three main things in its lifetime.  
(1)  Initialize  
(2)  Interpret  
(3)  Terminate  

The shell should support pipe (|), service (&), and file redirection (<, >, >>).
The following commands (with their traditional objective)should be implemented:  
cd:
```bash
cd [directory]
```
‘~’, `..`, ‘/’ are valid (along with alphanumeric characters) and stand for traditional meaning.  
pwd:
```bash
pwd [OPTION]
```
ls: 
```bash
ls [OPTION]... [FILE]...
```
Option: -l, -r, -s, --file-type (match file extension).  
Exit:
```bash
exit
```
Quite the shell (Terminate).

## Programming Language used
C++

## Contributors
Weili, Shi  
Sixiang, Zhang

## How to run
run the following command.  
```bash
./shell
```
## License
[License](https://github.com/DamoSWL/8000_Shell/blob/master/LICENSE)