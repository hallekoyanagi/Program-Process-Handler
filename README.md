# Program-Process-Handler
## Description:
Academic Project - Third Year

Written in C



## To Run:
in terminal,

run makefile using command
	make -f Makefile
 
run program using command
	./pman
	
## Known Issues:
1. if a user trys running a file that does not exist, the file still comes up in the list when bg list is called and disappears when bg destroy us called. This does not affect other processes however. The origin of the PID of this "process" is currently unknown.
