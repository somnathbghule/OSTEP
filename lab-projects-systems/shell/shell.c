#include <stdlib.h>
#include <stdio.h>
#include <shell.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

typedef struct cmd {
	char bin[32];
	char argv[1024];
}cmd;

int parseCmd(const char *argv, cmd *c){
	int i = 0;

	while( argv[i] ) {
		if( i==0 ) {
			while ( argv[i] && argv[i] != ' ' ) {
				c->bin[i] = argv[i];
				i++;		
			}	         			  		
		}else if (*(argv+i-1) ){
			strcpy(c->argv, argv+i+1);	
			break;
		}
	}
	return 0;
}

int executeShell(cmd c){

	int cfd;
	int status = 0;
	cfd=fork();
	int wstatus=0;

	if( cfd == 0 ){ //new child process
		if (*c.argv)
			status = execlp(c.bin, c.bin, c.argv, NULL);
		else
			status = execlp(c.bin, c.bin, NULL, NULL);

	}
	wait(&wstatus);
	return status;
}


int main(int argc, char **argv) {


	char buf[512];
	cmd c;
	c.bin[0]='\0';
	c.argv[0]='\0';
	while (1){

		printf("sh$ ");
		//scanf("%[^\n]",buf);	
		gets(buf);
		printf("inputwas:\"%s\"\n",buf);
		parseCmd(buf, &c);	
		executeShell(c);
		c.bin[0]='\0';
		c.argv[0]='\0';
	}

	//return 0
	return (0);
}
