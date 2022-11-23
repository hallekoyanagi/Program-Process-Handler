# Program-Process-Handler
## Description:
Academic Project - Third Year

Written in C

A program that uses fork() and parent/child processes to handle background processes. These processes are handled based on user input in the terminal. Available user commands include:

### 1. ``` bg <filename> ```
This command begins execution of the file with file name *filename*. If the file does not exist, user is informed by a message in the terminal. (See issue 1)

### 2. ``` bgkill <pid> ```
This command terminates the process with process ID *pid* by sending the the process the TERM signal. This has no affect on already terminated processes.

### 3. ``` bgstop <pid> ``` 
This command pauses the process with process ID *pid* by sending the the process the STOP signal. This has no effect on already stopped processes.

### 4. ``` bgstart <pid> ``` 
This command restarts a the process with process ID *pid* that was previously stopped by sending the the process the CONT signal. This has no affect on processes that are not stopped.

### 5. ``` pstat <pid> ```
This command prints out statistics related to the process with process ID *pid* to the terminal.

If no process at process ID *pid* exists, commands 2 thru 5 print an error message to the terminal.

## To Run:
in terminal,

run makefile using command
	make -f Makefile
 
run program using command
	./pman
	
## Known Issues:
1. if a user trys running a file that does not exist, the file still comes up in the list when bg list is called and disappears when bgkill is called. This does not affect other processes however. The origin of the PID of this "process" is currently unknown.
