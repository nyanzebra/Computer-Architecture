This is Project 1
================= 

Group  and Names:
-----------------
Group 28

Robert Baldwin and Ian McPherson


Description of Source Code:
-----------------------------
Both Accumulator Sim and Stack Sim can be found with the machine folder in src. The goal of this is to be able to load machines on top of a base machine. Once executed, you can easily switch between both machines and executed the correct corresponding files. You will not be able to execute the accum_sim.s with the stack machine and visa versa. You must open the correct .s file before starting the corresponding machine. If you need any help, type "help".

Instructions to compile:
------------------------
Navagate into the correct directory via command line and type "./compile_machine_shell.sh"

To run:
-------
Type in command line "./machine"

type help for list of commands and their arguments.

Example Input While Running The Machines:
-----------------------------------------

dir /PATH_TO_.S_CODE/ (must end with '/')

open stack_sim.s (or whatever your assembly file is called)

start -s (start with appropriate flags type help for details)


Design Issues:
--------------
We ran into issues initially on how to load in the assemply file and load it into instructions and data. Once we had succesfully implemented that, we had to figure out how we wanted the memory system to work and how to map the variable memory addresses with their alliases. Finally, we then had to figure out how to load the instruction and execute it for both the accumulator and stack machines. 


