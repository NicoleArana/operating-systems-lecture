#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main() {
 	char command[100];
	pid_t pid;
	printf("Nicole's terminal>>\n");

	while (true){

		printf("Enter your command>>: ");
		scanf("%[^\n]%*c", command);

		char delimiter[] = " ";
		char *token;
		char *segments[10]; // Array of pointers to store segment pointers
		int segment_count = 0;

		// Tokenize the input string using strtok
		token = strtok(command, delimiter);

		// Loop through tokens and store them in the 'segments' array
		while (token != NULL && segment_count < 10) {
			segments[segment_count] = token;
			segment_count++;
			token = strtok(NULL, delimiter); // Get the next token
		}

		// Add a NULL pointer at the end of the 'segments' array as required by execvp
		segments[segment_count] = NULL;

		/* fork a child process */
		if(strcmp(segments[0], "exit") == 0){
			exit(0);
		}

		if (strcmp("", segments[0]) == 0) {
			continue;
		}

		pid = fork();
		if (pid < 0){
			/* error occurred */
			fprintf(stderr, "Fork Failed");
			exit (-1) ;
		}else if (pid == 0) {
			/* child process */
			execvp(segments[0],segments);
			
		}else{/* parent process */
		/* parent will wait for the child to complete */
		wait(NULL);
		}
	}
}
