# Operating Systems and Networks, Monsoon 2022
# Creating a User-defined Interactive Shell Program 
# Gowlapalli Rohit

>##### All these commands are tested on Ubuntu Version 20.04.3 LTS (Focal Fossa) 
```
2021101113
├── autocompletion.c
├── autocompletion.h
├── bg.c
├── bg.h
├── cd.c
├── cd.h
├── ctrlc.c
├── ctrlc.h
├── ctrlz.c
├── ctrlz.h
├── discover.c
├── discover.h
├── echo.c
├── echo.h
├── fg.c
├── fg.h
├── headers.h
├── history.c
├── history.h
├── history.txt
├── io_redirection.c
├── io_redirection.h
├── jobs.c
├── jobs.h
├── linked_list.c
├── linked_list.h
├── linked_main.c
├── ls.c
├── ls.h
├── main.c
├── makefile
├── pinfo.c
├── pinfo.h
├── pipe.c
├── pipe.h
├── process_command.c
├── process_command.h
├── prompt.c
├── prompt.h
├── PWD.c
├── PWD.h
├── README.md
├── sig.c
├── sig.h
├── sig_handler.c
├── sig_handler.h
├── spec4.c
├── spec4.h
├── str_tok_and.c
└── str_tok_and.h

```

* >Commands to be executed
```bash
thecodebuzz@DESKTOP-NUEMRRD:~$ make
thecodebuzz@DESKTOP-NUEMRRD:~$ ./main
```
* > Neglect all warnings during execution of make file-they are just errors due to unused variables
<hr>

* >
|File name|Purpose|Features|Related Functions|
|:--------:|:-----:|:------:|:---------------:|
|main.c|Extracts input from commandline and Runs Shell Loop|Tokenises the input with delimiter ";" & handles ctrld comand & handles invalid syntax|main() & strtok()|
|prompt.c|Prints Prompt|Handles time taken by a foreground process|prompt()|
|str_tok_and.c|Handles the criterion for an input commnad to be background/foreground|Tokenises its input with the delimiter "&"|str_tok_and(),strtok()|
|pipe.c|Handles Command PipeLines|Tokenises its input with the delimiter "\|\"|pipe_to_process_command() & str_tok_pipe() & strtok()|
|process_command.c|Calls all implemented command functions|Handles I/O Redirection & Tokenises its input with " "|str_tok_whitespaces() & strtok()|
|cd.c|Implements cd command|Changes the Directory|cd_func() & chdir() & getcwd()|
|PWD.c|Implements pwd command|Prints name of current working directory|pwd_func() & getcwd()|
|ls.c|Implements ls command|Lists Directory contents|print_ls() & scandir() & lstat() & qsort() & getpwuid() & getgrgid() & time()|
|echo.c|Implements echo command|Writes arguments to standard output|echo_func()|
|pinfo.c|Implements pinfo command|Reads info files|pinfo() & readlink() & fopen()|
|history.c|Implements history command|Displays GNU History Library|print_history() & readfromhistory() & writetohistory() & fopen()|
|discover.c|Implements discover command|Searches for files/directories in a directory hierarchy|discover() & dfs() & opendir() & readdir() & stat()|
|spec4.c|Implements commands in bg/fg|Runs/Terminates processes in bg/fg|bg_func() & fg_func() & signal() & fork() & execvp() & waitpid()|
|jobs.c|Prints info related to list of all currently running bg processes spawned by shell|Lists commandnames in alphabetical order with pid & status|jobs() & fopen()|
|sig.c|Takes job number of running job & sends signal corresponding to the signal number to process|Throws error if no job with given number exists|sig_func() & kill()|
|fg.c|Brings running/stopped bg job corresponding to job number to fg & changes its state to running|Throws an error if no job with given job number exists|FG() & signal() & tcsetpgrp() & setpgid() & kill() & getpgid()|
|bg.c|Changes the state of a stopped background job to running|Throws error if no background job corresponding to given job number exists|BG() & kill()|
|ctrlc.c|Interrupts any currently running fg job|Has no effect on the shell if no fg process is running|ctrlc() & sprintf() & write() & fflush()|
|ctrlz.c|pushes any currently running fg job into the bg & changes its state from running to stopped|Has no effect on the shell if no fg process is running|ctrlz() & sprintf() & write() & fflush()|
|autocompletion.c|When tab key is pressed ,it prints all files which have same starting letters as ls command and then again show the same prompt|If there is only 1 file/folder which has the same starting characters, the prompt will be filled with that|autocomplete() & scandir() & qsort() & stat()|
|history.txt|Used to implement history command|Stores each new command on a new line|-|

```
Specification 1: Display requirement
prompt-display format ::  <username@system_name:curr_dir>

Assumptions:

1) It is assumed that
   a) strlen( absolute_path to the home directory of the shell ) <=300
   b) strlen( curr_dir in display prompt ) <=300
   c) strlen( system_name) <= 200
   d) strlen( username) <= 200
   e) strlen( Time taken by foreground process ) <=300
   f) strlen( input ) <=1000
   g) strlen( absolute_path to history.txt) <=625
2) getline() is used to read the input received on displaying the prompt
3) Input is tokenised with following delimiters in order (";","&"," ")


```
```

Specification 2: Builtin commands

execvp or similar commands were not used to implement these commands

Command type : "cd"

a) cd < Directory Path > / <Directory Name>
   i) If the Directory path is valid ,then the working directory is changed to the corresponding Directory Path
   ii) If the Directory Path is invalid , then perror is Displayed
b) cd -
   i)prints the previous working directory and shifts to the previous working directory
   ii)If there is no such previous working directory, "OLDPWD NOT SET" is printed on to the display screen.
c) cd ~ / cd 
  working directory is changed to the home-directory of the shell

Command type : "echo"

echo <arg1> <arg2> ............ <argn>

a) It is assumed that command echo can have any number of arguments
b) echo writes arguments to standard output
c) multi-line strings and environmental variables are not handled

Command type : "pwd"

pwd <arg1> <arg2> ............. <argn>

a) pwd command writes the full pathname of the current working directory to the standard output.

b) As the presence of other arguments doesnt affect processing "pwd" in accordance with Linux-Shell, any number of arguments can be given to pwd

```
```

Specification 3: ls command


"ls" command-lists directory contents
execvp or similar commands were not used to implement these commands

a) ls <Directory Name>/<Directory Path>/<File_name>/<File_path>
   i) If the Diectory path is valid ,then all the contents of the directory entry get displayed onto the screen
   ii) If multiple such directory paths/File paths,all the contents of each directory entry get displayed onto the screen,Directory entries of a Directory are printed after printing the name of the directory
   iii) If the Directory Path is invalid , then perror is Displayed

b) ls -a <Directory Name>/<Directory Path>/<File_name>/<File_path>
do not ignore  directory entries starting with .

c) ls -l 
displays extra information regarding files

d) ls < arguments in (a) > < arguments in (b) > < arguments in (c) >
displayed according to the union of all the printing combinations

e) ls command lists all the directory entries in alphabetical order

f) In ls -l ,if the last-modfied time of a directory and the current_time differ by more than 6 months-then, <month> <day> <Year> unlike <month> <day> <Hours>:<Minutes> in other cases

g) It is assumed that directory name would not contain any spaces

h) colours are assigned for different types of directory entries
    green-executables
    white-files
    blue-directories
```
```

Specification 4: System commands with and without arguments :
Specification 6: Finished Background Processes [5 marks]

Foreground process ->  shell waits for process to complete and regain control when this process exits.

Background process -> shell will spawn that process and doesn't wait for the process to exit

a)If the input is of the form:
<command-1>&<command-2> &... &..&<command-(n-1)>&<command-n>
shell runs all the commands of the form <command-j> where 1<=j<n in the background and <command-n> is run in the foreground.

b) If T=Time taken by the foreground process
 i) If T>=1 ,next prompt: <username@system_name:curr_dir took Ts>
 ii) next prompy: <username@system_name:curr_dir>

c) Background processing for built-in commands is not handled like ls,echo,pwd,pinfo,cd

d)Multiple background processes can be run in the background

e) Whenever a new background process is started, the PID of then newly created background proess is printed on to the display screen

f) If a background process exits,then the shell displays the appropriate message to the user

g) commands like fork(),waitpid(),execvp(),signal() are used in addition to use of a Doubly Linked list to indicate the process-number

h) It is assumed that strlen(any argument) <= 600

```
```
Specification 5: pinfo command

pinfo <pid> - prints the process info of the given pid
pinfo - prints the process-related info of your shell program

a) If /proc/<pid>/stat or /proc/<pid>/exe is unaccesible,then appropriate perror is displayed
b) commands like getpid(),fopen(),fscanf(),fclose(),readlink(,,) are used to implement this command
c) It is assumed that a maximum of 52 entries can be present in /proc/<pid>/stat
d) It is assumed that strlen(/proc/<pid>/stat) <=800 and strlen(/proc/<pid>/exe) <=800 and strlen(buffer written into in readlink)<=500
e) '+' is added to the status code if the process is in the foreground
f) commands like getpid(),fopen(),fscanf(),readlink() are used to implement pinfo
g) If the executable path directs to a path which resides inside the home-directory of the shell,the prefix-path of the homedirectory of the shell is replaced by ~

Display Format of pinfo command:
pid : <pid>
process Status : {R/S/S+/Z}
memory : {<Virtual Memory>}
executable Path : <path>
```
```

Specification 7: Discover command

command format : discover <target_dir> <type_flags> <find_name> (fixed-format) (Total-16 cases) (<type-flags> ∈ {-d,-f})

a) DFS is used along with opendir() and readdir() to implement the discover command
b) scandir command may not be prefered to iterate over the directory entries as scanddir automatically mallocs the name_list thereby causing a possibility of stack_frame to pile-up and give rise to seg_fault
c) perror is displayed if one of the paths redirected to is invalid 
d) Some of the syntax-error cases in discover command are not handled
e) I have not handled cases like discover -df and discover -fd as those cases are not mentioned in the document as its mentioned that -d searches for all directories and -f searches for all files but there is no definition for -df and -fd which are not defined.

```
```
Specification 8: history
command type : history

a) history.txt is used to maintain the last 20 commands executed through the shell
b) history command prints a maximum of the last 10 commands executed through the shell
c) command is not stored in history if it is the exactly same as the previously entered command.
d) empty commands and commands with just whitespace characters are not handled properly
e) oldest commands are overwritten if more than 20 commands are entered
f) The commands are tracked across multiple sessions of shell
g) It is assumed that strlen(command) < 400 to be able to display it in history.txt

```
```
Specification 9:Input/Output Redirection

Assumptions:

1) It is assumed that a command belongs to only one of the following 9 possible commands
   a) arg1 > arg2
   b) arg1 < arg2
   c) arg1 >> arg2 
   d) arg1 > arg2 < arg3
   e) arg1 < arg2 > arg3
   f) arg1 >> arg2 < arg3
   g) arg1 >> arg2 > arg3
   h) arg1 > arg2 >> arg3
   i) arg1 < arg2 >> arg3
2) Input is tokenised with following delimiters in order (";","&","|"," ")
3) It is assumed that >/</>> are obtained as seperate tokens after tokenising through all delimiters


```
```

Specification 10: : Command Pipelines

Command format : arg1 | arg2 | arg3 |.........| argn  (where argi!=(/t+/r+/n+' ')* for all i such that 1<=i<=n)
Assumptions:
a) It is assumed that number of tokens obtained after tokenising input with "|" <=1000
b) Any error in pipelining would result in display of perror()
c) Piped commands are not executed concurrently (not using fork() as waitpid() must be used which is equivalent to not using fork())


```
```

Specification 11:  I/O Redirection within Command Pipelines
Assumptions:
a) Input is tokenised with following delimiters in order (";","&","|"," ")
b) Use of * may not be advisable

```
```

Specification 12:  User-defined Commands

Command Type-jobs:

Valid command : jobs / jobs -r / jobs -s

a) list of all currently running background processes is sorted w.r.t main-command (for example : "sleep" in "sleep 30")

b) It is assumed that if the state of a job is not "stopped",then its state is "running"

c) It is assumed that strlen(/proc/stat/<pid>)<=800

Command Type-sig:

Valid command : sig <job number> <signal number>

a) perror() is displayed if the supplied job number is invalid / invalid syntax in sig command

Command Type-fg:

Valid command : fg <job number> 

a) perror() is displayed if the supplied job number is invalid / invalid syntax in sig command

Command Type-bg:

Valid command : bg <job number> 

a) perror() is displayed if the supplied job number is invalid / invalid syntax in sig command


```
```

Specification 13: : Signal Handling 

Command Type- CTRL-Z:
a) New prompt is printed if there is no foreground process running
b) pushes any currently running foreground job into the background, and changes its state from ‘running’ to ‘stopped.’ 

Command Type- CTRL-C:
a) Only 1 currently running foreground job is interrupted in a set of multiple of foreground job commands per CTRL-C command
b) New prompt is printed if there is no foreground process running
c) interrupts any currently running foreground job, by sending it the SIGINT signal

Command Type- CTRL-D:
a) Code for CTRL-D is handled in the Raw-mode Driver code (^D is not displayed on executing this command)
b) logs out of the shell , without having any effect on the actual terminal.

```
```
Specification 14: Autocompletion

a) "." and ".." are omitted for consideration to match prefix of names of directory entries and these both directory entries are not autocompleted if tried to do so
b) <inbuilt command> <tab> cases are not handled (Like ls <tab> autocompletes to ls.txt if there is a file in the current directory called "ls.txt")
c) When <tab> key is pressed
  i) If there is only one file/folder which has the same starting characters, the prompt is filled with that
    I) If it's a file, a space is placed after the file 
    II) If it’s a folder, a ‘/’ is put after the folder name
  ii) else
     all directory_entry_names are printed which have the same starting letters (as the ls command) and then same prompt is showed again(autocompleted to common prefix)
d) Cases having spaces between tokens are also handled (except the cases in (b))
e) autocomplete involving '/' as path is not handled (root)
f) If no matching entries are found, cursor remains in its earlier position ( sound is not implemented )
g) If <tab> is pressed with an whitespace-string as input , then all directory entries are printed (except "." and "..")
h) hidden files are considered as valid directory entries unlike "." and ".."

```
