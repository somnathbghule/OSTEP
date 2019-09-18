#include <stdlib.h>
#include <stdio.h>
#include <shell.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAXARGS 10

#define IS_CHAR_SPACE(c) (c==' ')
#define IS_CHAR_PIPE(c) (c=='|')
#define IS_CHAR_NULLTERM(c) (c=='\0')
#define IS_CHAR(c) ( ( c>='a' && c <='z' ) || ( c>='A' && c<='Z' ) || (c=='.') || (c=='-') || (c=='"') )

int word( const char *src, char *buf ) {
        int ind = 0;
	int bind=0;
	buf[0]='\0';
	if (IS_CHAR_SPACE(*(src+ind))){
		ind++;			
	}
        while ( *(src + ind) ){
                if( IS_CHAR_SPACE(*(src+ind)) /*|| !IS_CHAR( *(src+ind) )*/){
                        break;
                }
                buf[bind++]=*(src+ind);
                ind++;
        }
        buf[bind]='\0';
        return ind;
}

int strCpy( const char *src, char *dest ) {
        int ind=0;
        while( *(dest +ind)=*(src+ind) ) ind++;

        *(dest+ind)='\0';
        return 0;
}

typedef struct cmd {
	char type;
	int argc;
	char *argv[MAXARGS];
} cmd;

typedef struct pipecmd {
	char type;	
	cmd *left;
	cmd *right;
}pipecmd;

cmd* parseCmd( char *argv ){
	dprintf("inputwas:\"%s\"\n",argv);
	cmd *c=(cmd *)malloc(sizeof(cmd));
	c->type=' ';
	pipecmd *pcmd = (pipecmd *)malloc(sizeof(pipecmd));
	int i = 0;
	int count=0;
	char buf[128];
	count=word(argv, buf);
	i+=count;
	int argc=0;	
	c->argv[argc]=(char *)malloc(count);
	strCpy(buf, c->argv[argc]);
	argc++;	
	while( *(argv+i) ){
		buf[0]='\0';
		count=word(argv+i,buf);
		if( IS_CHAR_PIPE(*buf) ){
			pcmd->type='|';
			pcmd->left=c;	
			c->argc=++argc;
			c->argv[argc]='\0';
			c = (cmd *)malloc(sizeof(cmd));
			c->type = ' '; 
			argc=0;
			i+=count;
			continue;
		}
		c->argv[argc]=(char *)malloc(count-2); 
		strCpy(buf, c->argv[argc]);
		argc++;
		i+=count;
	}
	c->argc=argc;
	c->argv[argc]='\0';
	if ( IS_CHAR_PIPE(pcmd->type) ){
		pcmd->right = c;
		return (cmd *)pcmd;
	}else{
		free(pcmd);
		pcmd=NULL;
	}
	return c;
}

int freecmd( cmd *c );
int executeCmd(cmd *c);
int executepipecmd( pipecmd * pc ){
	
	int p[2];
	int wstatus=0;
	pipe(p);
	int cfd = fork();
	if( !cfd ) { //left	
		//dup2(p[1], 1);
		//close(p[0]);
		//executeCmd( pc->left );
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		cmd *c = pc->left;
		execvp(c->argv[0], c->argv);

	} else { //right
		//dup2(p[0], 0);
		//close(p[1]);
		//executeCmd( pc->right );
		close(0);
                dup(p[0]);
                close(p[0]);
                close(p[1]);
		cmd *c = pc->right;
		wait(&wstatus);
		execvp(c->argv[0], c->argv);
	}
	freecmd(pc->left);
	freecmd(pc->right);
	pc = NULL;
	return 0;
}

int executeCmd(cmd *c) {
	int cfd;
	int status = 0;
	dprintf("arc: %d\n", c->argc);	
	dprintf("type: %c\n", c->type);	
	dprintf("argv[0]: %s\n", c->argv[0]);	
	dprintf("argv[1]: %s\n", c->argv[1]);	
	cfd=fork();
	int wstatus=0;
	
	if( cfd == 0 ){ //new child process
		if (c->argc)
			status = execvp(c->argv[0], c->argv);

	}
	wait(&wstatus);
	freecmd(c);
	return status;
}

int executeShell(cmd *c){
	int status = 0;
	switch (c->type){
		case ' ':
			executeCmd(c);
			break;
		case '|':
			executepipecmd((pipecmd*)c);
			break;
		default:
			printf("default\n");
			break;
	}
	return status;
}

int freecmd( cmd *c ) {
	while(c->argc>0){
		--c->argc;
		free(c->argv[c->argc]);	
		c->argv[c->argc]=NULL;
	}
	free(c);
	c=NULL;
	return 0;
}

int main(int argc, char **argv) {

	char buf[128];
	int nbuf=sizeof(buf);
	cmd *c;
	while (1) {
		printf("sh$ ");
		memset(buf, 0, nbuf);
		fgets(buf,nbuf,stdin);
		buf[strlen(buf)-1]='\0';
		c = parseCmd( buf );	
		executeShell(c);
	}

	//return 0
	return (0);
}
