#include <cstring.h>


void swapStrings(char **str1, char **str2){
	char *temp=*str1;
	*str1=*str2;
	*str2=temp;
}

/*
 reference code;
 void assending_order(int *arr){
        cout<<"assending_order"<<endl;
        for ( int first=0; first<BUF_SIZE; first++ ){
                for ( int second=first+1; second<BUF_SIZE; second++ ){
                        if(arr[first]>arr[second]){
                                swap(arr+first, arr+second);
                        }
                }
        }
}
*/

void sortStrings(char **arr, int asize) {

	for (int it=0;it<asize;it++){
		for (int jt=it+1;jt<asize;jt++){
			CString first(arr[it]);
			CString second(arr[jt]);
			if ( !(first < second) ){
				swapStrings(&arr[it], &arr[jt]);
			}
		}	
	}

}

void showSortedOutput( char **arr, int asize ){
	
	int i=0;
	while( i < asize  ){
		cout<< arr[i++] <<endl;
	}
}


void readFileFillArray(char *filename, char **arr, int *asize){
	*asize = 0;
	int fd = open(filename, O_RDONLY);
	if( fd==-1 ){
		printf("open failed\n");
		return;
	}

	char buf[1];
	char tempBuf[1024];
	int i=0;
	int j=0;
	while ( read(fd,buf,1) == 1 ){

		if (*buf==EOF){
			break;
		}
		if ( *buf != '\n' ){
			tempBuf[i++]=*buf;
		}else {
		
			tempBuf[i]='\0';			
			arr[j] = (char *)malloc(sizeof(char)*i);
			strcpy(arr[j], tempBuf);
			i=0;
			j++;
		}		
	}
	*asize=j;
	close(fd);
}

int main(int argc, char **argv){

	char * arr[1024] ;
	int asize=0;

	if ( argc != 2 ){
		cout<< argv[0]<<endl;
		return 0;
	}
	
	readFileFillArray(argv[1], arr, &asize);

	//showSortedOutput(arr, asize);
	sortStrings(arr, asize);
	showSortedOutput(arr, asize);

	//return 0
	return (0);
}

