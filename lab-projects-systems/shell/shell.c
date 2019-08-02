#include <stdlib.h>
#include <stdio.h>
#include <shell.h>
#include <unistd.h>


int executeShell(const char *argv){

	int fd;
	fd=fork();

	if( fd == 0 ){ //new child process
		execlp(argv, argv, NULL);

	}
	
	return 0;
}


int main(int argc, char **argv) {


	char buf[512];

	while (1){
		printf("\nsh$ ");
		scanf("%s",buf);	
		executeShell(buf);
	}

	//return 0
	return (0);
}
