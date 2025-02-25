/*
project: 01
author: Cynthia Abid
email: cabid1@umbc.edu
student id: AT47574
description: a simple linux shell designed to perform basic linux commands
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include "utils.h"

/*
In this project, you are going to implement a number of functions to
create a simple linux shell interface to perform basic linux commands
*/

/*
DEFINE THE FUNCTION PROTOTYPES
user_prompt_loop()
get_user_command()
parse_command()
execute_command()
*/
void user_prompt_loop();
char *get_user_command();
char **parse_command(char *str);
void execute_command(char **input);
char *conCatHelp(char *proc, char *rest);
void display_proc(char *proc);


int main(int argc, char **argv) {
	/*
	Write the main function that checks the number of argument passed to ensure
	no command-line arguments are passed; if the number of argument is greater
	than 1 then exit the shell with a message to stderr and return value of 1
	otherwise call the user_prompt_loop() function to get user input repeatedly
	until the user enters the "exit" command.
	*/

	if (argc>1) {
		fprintf(stderr,"too many arguments \n");
		exit(1);
	} else {
		user_prompt_loop();
	}
	return 0;
}

/*
user_prompt_loop():
Get the user input using a loop until the user exits, prompting the user for a command.
Gets command and sends it to a parser, then compares the first element to the two
different commands ("/proc", and "exit"). If it's none of the commands,
send it to the execute_command() function. If the user decides to exit, then exit 0 or exit
with the user given value.
*/

void user_prompt_loop() {

	/*
	Functions you may need:
	    get_user_command(), parse_command(), execute_command(), strcmp(), strcat(),
	    strlen(), strncmp(), fopen(), fclose(), getline(), isdigit(), atoi(), fgetc(),
	    or any other useful functions
	*/
	// set up

	//1. prompt the user to type command by printing >>
	printf(">>");
	//2. get the user input using get_user_command() function
	char *command = get_user_command();
	//3. parse the user input using parse_command() function
	char **parse = parse_command(command);
	//loop:
	while(strcmp(parse[0],"exit") != 0) {
               //printf("made it into the loop!\n");
		//5. if the first element is "/proc" then you have the open the /proc file system to read from it
               // add to hidden file used this https://www.w3schools.com/c/c_files_write.php
              // Open the file in append mode
               FILE *file = fopen(".421sh", "a");
               //printf("opened file!\n");                
                fprintf(file, "\n%s", command);
                // Close the file
                fclose(file);
                //printf("added command and closed file\n");
		if (strcmp(parse[0],"/proc") == 0) {
                  //i) concat the full command: Ex: user input >>/proc /process_id_no/status concated output: /proc/process_id_no/status
	          char *con = conCatHelp(parse[0],parse[1]);
		  //ii) read from the file line by line. you may user fopen() and getline() functions
		  display_proc(con);
                  free(con);
                }else if(strcmp(parse[0],"history") == 0){
                        display_proc(".421sh");
		}else{
			// 7. otherwise pass the parsed command to execute_command() function
			//printf("executing!!\n");
                        execute_command(parse);
		}
		free(command);
                printf(">>");
		command = get_user_command();
                int k = 0;
                while(parse[k] != NULL) {
                   free(parse[k]);  // Free each individual command
                   k++;
                }
                free(parse);  // Finally free the list itself
                
		parse = parse_command(command);

	}
	//6. if the first element is "exit" the use the exit() function to terminate the program
        free(command);
        int k = 0;
        while(parse[k] != NULL) {
            free(parse[k]);  // Free each individual command
            k++;
        }
        free(parse);  // Finally free the list itself
                
}

/*
get_user_command():
Take input of arbitrary size from the user and return to the user_prompt_loop()
*/

char *get_user_command() {
	/*
	Functions you may need:
	    malloc(), realloc(), getline(), fgetc(), or any other similar functions
	*/
        //set up var
	char *input;
	char letter;
	int index = 0;
        //allocate mem
	input = (char*)malloc(1*sizeof(char));
        //get char from user
	letter = getc(stdin);
        //while not at end
	while(letter!='\n') {
                //set first index to char increase the index realloc restart loop
                //was not setting var to realloc before that was a bad time
		input[index] = letter;
		index++;
		input = realloc(input,index*sizeof(char));
		letter = getc(stdin);
	}
        // if you dont set this it sets to garbage data that was fun to debug
	input[index] = '\0';
        //printf("hello from get_user\n");
        //printf("%s\n",input);
        
	return input;
}

/*
parse_command():
Take command grabbed from the user and parse appropriately.
Example:
    user input: "ls -la"
    parsed output: ["ls", "-la", NULL]
Example:
    user input: "echo     hello                     world  "
    parsed output: ["echo", "hello", "world", NULL]
*/

char **parse_command(char *str) {
	//set up var
	char **list = NULL;
	char *word;
	int index;
	int count = 0;
	int i;
	//during debugging wanted to check length was right
	//printf("%d\n",(int)strlen(str));
	for(i = 0; i < (int)strlen(str); i++) {
		//during debugging wanted to check index
		//printf("%d\n",i);
		//anytime we reach a space need to increment
		while(str[i] == ' ') {
			i++;
		}
		//resetting var
		index = 0;
                //give it some space
		word = (char*)malloc(1*sizeof(char));
		//check not at end or at space
		while(str[i] != ' ' && str[i] != '\0') {
                        //again set realloc to word debugg issue
			word = realloc(word, (index + 2)*sizeof(char));
			word[index] = str[i];
			index++;
			i++;

		}
        
		//put word in list and set last index to null terminator or it gets funky
                word[index] = '\0';
		list = realloc(list,(count+2)*sizeof(char*));
		list[count] =word;
		count++;
	}
        //i was checking that everything was in the proper format
        //printf("hello from parse\n");
        //int k = 0;
        //while(list[k] != NULL){
           // printf("%s\n",list[k]);
           // k++;
        //}
        //if (list[k] == NULL){
          //printf("NULL\n");

        //}
        list[count] = NULL;

	return list;
}

/*
execute_command():
Execute the parsed command if the commands are neither /proc nor exit;
fork a process and execute the parsed command inside the child process
*/
//used newproc-posix.c from professor as example
//and https://linux.die.net/man/3/waitpid to understand waitpid()
// and https://www.digitalocean.com/community/tutorials/execvp-function-c-plus-plus to understand execvp()
void execute_command(char **input) {
	/*
	Functions you may need:
	    fork(), execvp(), waitpid(), and any other useful function
	*/
        //professor structure example
	pid_t pid;
        //me checking valid
	char *proc = "/proc";
	char *nope = "exit";
	if(strcmp(input[0],nope) != 0 && strcmp(input[0],proc) != 0) {
		pid = fork();
		if (pid < 0) { /* error occurred */
			perror("Fork Failed");
			return;
		}
		else if (pid == 0) { /* child process */
                        //execute command
			if(execvp(input[0],input) == -1) {
				perror("execvp failed");
				exit(1);
			}
		}
		else { /* parent process */
			/* parent will wait for the child to complete */
			int stat;
			printf("I am the parent\n");
                        //dont want a zombie
			waitpid(pid, &stat, 0);
                        //check if terminate properly
			if(WIFEXITED(stat))
				printf("Child Complete\n");
		}
	}


}
//used this https://www.tutorialspoint.com/c_standard_library/c_function_fopen.htm to look into fopen
// and https://c-for-dummies.com/blog/?p=1112 for getline i think i may have already cited this but too tired to check
void display_proc(char *proc) {
	FILE *file = fopen(proc, "r");
	if (file == NULL) {
		perror("Error opening file");
		return;
	}

	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, file) != -1) {
		printf("%s", line);
	}

	free(line);
	fclose(file);
}

//used this to understand strcat https://www.geeksforgeeks.org/strcat-in-c/#
char *conCatHelp(char *proc, char *rest) {
	char *temp;
	temp = (char *)malloc((strlen(proc) + strlen(rest) + 1) * sizeof(char));
	strcpy(temp, proc);
	strcat(temp, rest);
	return temp;
}
