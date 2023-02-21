//Justin Moore
//CS-390 Linux
//2-21-23
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MAX_ARGS 3
#define MAX_LINE 256
#define DELIMITERS " \t\n"



void execute_command(char* user_prompt, int argc, char ** argv) {

	if (argc == 0) {                                                            //if no arguments then do nothing
		return;
	}
	if (strcmp(argv[0], "echo") == 0) {                                         //executing echo command(print inputs to the screen)
		if (argc == 1) {                                                        //executing echo command(print nothing)
			printf("\n");
			return;
		}
		if (strcmp(argv[1], "-n") == 0) {                                       //executing echo command(print argument, no carriage return)
			for (int i = 2; i < argc; i++) {
				printf("%s ", argv[i]);
			}
		} else {                                                                //executing echo command(print argument, with carriage return)
			for (int i = 1; i < argc; i++) {
				printf("%s ", argv[i]);
			}
			printf("\n");
		}
	} else if (strcmp(argv[0], "PS1") == 0) {                                   //executing PS1 command(changes the symbol in command prompt at beginning of input line)
		if (argc != 2) {                                                        //executing PS1 command(not enought args, displays error)
			printf("Usage: PS1 new_prompt\n");
			return;
		}
        char str[] = " ";
        strncat(argv[1], str, 1);
		strcpy(user_prompt, argv[1]);
	} else if (strcmp(argv[0], "cat") == 0) {                                   //executing cat command(displays contents of a file)
		if (argc != 2) {                                                        //executing cat command(not enought args, displays error)
			printf("Usage: cat file\n");
			return;
		}
		char* filename = argv[1];
		FILE* file = fopen(filename, "r");
		if (file == NULL) {                                                     //executing cat command(can not find file, displays error)
			printf("Error: Unable to open file %s\n", filename);
			return;
		}
		char c = fgetc(file);
		while (c != EOF) {                                                      //executing cat command(reads chars from file and displays to console until end of file)
			printf("%c", c);
			c = fgetc(file);
		}
		fclose(file);
	} else if (strcmp(argv[0], "cp") == 0) {                                    //executing cp command(used for copying file; source and destination files as arguments)
		if (argc != 3) {                                                        //executing cp command(if anything other than three args, displays error)
			printf("Usage: cp source_file destination_file\n");
			return;
		}
		char* source_filename = argv[1];
		char* destination_filename = argv[2];
		FILE* source_file = fopen(source_filename, "r");
		if (source_file == NULL) {                                              //executing cp command(no source filename, displays error)
			printf("Error: Unable to open file %s\n", source_filename);
			return;
		}
		FILE* destination_file = fopen(destination_filename, "w");
		if (destination_file == NULL) {                                         //executing cp command(no destination filename, displays error)
			printf("Error: Unable to open file %s\n", destination_filename);
			fclose(source_file);
			return;
		}
		char c = fgetc(source_file);                                            //reading every char from source file and writing to destination file
		while (c != EOF) {
			fputc(c, destination_file);
			c = fgetc(source_file);
		}
		fclose(source_file);
		fclose(destination_file);
	} else if (strcmp(argv[0], "rm") == 0) {                                    //executing rm command(used for removing file; source and destination files as arguments)
		if (argc != 2) {                                                        //executing cp command(if anything other than two args, displays error)
			printf("Usage: rm file\n");
			return;
		}
		char* filename = argv[1];
		if (unlink(filename) != 0) {                                            //executing cp command(if unable to delete file, displays error; otherwise file is deleted)
			printf("Error: Unable to delete file %s\n", filename);
			return;
		}
	} else if (strcmp(argv[0], "mkdir") == 0) {                                 //executing mkdir command(command is used to create a new folder that will contain files)
		if (argc != 2) {                                                        //executing mkdir command(if number of args is not two, display error)
			printf("Usage: mkdir directory\n");
			return;
		}
		char* dirname = argv[1];
		if (mkdir(dirname, 0777) != 0) {                                        //executing mkdir command(if dir is able then we create dir with read, write, and execute permissions for users, groups, others; d = directory when viewing with ls -l)
			printf("Error: Unable to create directory %s\n", dirname);
			return;
		}
	} else if (strcmp(argv[0], "rmdir") == 0) {                                 //executing rmdir command(command is used to remove an existing folder that will contain no files; if you want to delete folder with files use rmdir -r, r = recursion)
		if (argc != 2) {                                                        //executing rmdir command(if number of args is not two, display error)
			printf("Usage: rmdir directory\n");
			return;
		}
		char* dirname = argv[1];
		if (rmdir(dirname) != 0) {                                              //executing rmdir command(if dir exists then remove, otherwise display error)
			printf("Error: Unable to delete directory %s\n", dirname);
			return;
		}
	} else if (strcmp(argv[0], "exit") == 0) {                                  //executing exit command(command is used to exit my shell)
		exit(0);
	} else {
		printf("Usage: Please enter a valid command\n");
	}
}


int main(char** argv) {


    char prompt[3] = "$ ";                                                      //prompt symbol
	char line[MAX_LINE];                                                        //line for user input
	char* args[MAX_ARGS];                                                       //inputs copied from the command lines argv


	while (1) {                                                                 //infinite loop

        int argc = 0;                                                           //declaring number of arguments here since we didn't need it from the actual cmd line
		printf("%s", prompt);
		fgets(line, MAX_LINE, stdin);                                           //reading input line

		char* arg = strtok(line, DELIMITERS);                                   //tokenizing the input line




		while (arg != NULL && argc < MAX_ARGS) {                                //loop while there is a valid string and num of args don't exceed max
			args[argc] = arg;                                                   //storing each argument as an index in a array for use by execute_command routine
			argc++;
			arg = strtok(NULL, DELIMITERS);                                     //use previous string with same delimiters
		}

		execute_command(prompt, argc, args);                                    //executing given command based on inputs and number of arguments(normally types of arguments as well).

	}


	return 0;



}
