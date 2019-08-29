#include <stdlib.h>
#include <stdio.h>
#include <shell.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct cmd {
	char bin[32];
	char argv[1024];
}cmd;

int parseCmd(const char *argv){
	int i = 0;
	while(argv[i]){
		if( i==0 ){
			
		}
		i++;
	}
}

int executeShell(const char *argv){

	int cfd;
	int status = 0;
	cfd=fork();
	int wstatus=0;

	if( cfd == 0 ){ //new child process
		status = execlp(argv, argv, NULL);

	}
	wait(&wstatus);
	return status;
}


int main(int argc, char **argv) {


	char buf[512];

	while (1){

		printf("sh$ ");
		//scanf("%[^\n]",buf);	
		gets(buf);	
		printf("inputwas:%s\n",buf);
		executeShell(buf);
	}

	//return 0
	return (0);
}
