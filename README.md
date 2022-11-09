# OS_homework

Write a program in C that uses system calls and UNIX library functions that meets the specifications described below.

The program consists of two processes. One of the processes uses an external command to generate the list of file names in a directory given as an argument on the program's command line. These names must go through a pipe to the other process.

As the data is available, the list will be processed by the other process, which will display, on a line at a time, the name, size, and owner identifier of each of the piped named files.

Hint: To issue an external command from within a process, one can use one of the exec... functions. A redirection of the standard output is also needed beforehand, in that process, for the data to reach the pipe.
