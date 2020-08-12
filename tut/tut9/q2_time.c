#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define PARENT_MSG_1 ("Hi! Do you know what time it is?")
#define CHILD_MSG_1 ("The time is 8:30 !")
#define PARENT_MSG_2 ("Thank you!")

#define PROMPT ("PROMPT!")

int main() {
	
	
	int parent_to_child[2];
	int child_to_parent[2];
	pipe(parent_to_child);
	pipe(child_to_parent);
	pid_t pid = fork();
	
	if(pid > 0) {
		printf("Parent: %s\n",PARENT_MSG_1);
		write(parent_to_child[1], PROMPT, strlen(PROMPT)+1); //Write first after 
		
	} else if (pid == 0) {
		char buf[8];// WAIT AND READ
		read(parent_to_child[0], buf, 8);
		
		printf("Child: %s\n", CHILD_MSG_1); //Print and then write back
		write(child_to_parent[1], PROMPT, strlen(PROMPT)+1);
		
	} else {
		fprintf(stderr, "Something broke with fork!\n");
	}
	
	return 0;
}
