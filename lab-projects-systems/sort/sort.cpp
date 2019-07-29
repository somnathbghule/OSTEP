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

int main(int argc, char **argv){

	char * arr []  = { "Somnath", "Bhaskar", "Ghule" };
	int asize = 3;

	if ( argc > 1 )
		cout<< argv[0]<<endl;

	CString cstring1("anc");
	CString cstring2("aNc");
	
/*	
	if( cstring1 < cstring2 ){
		cout<<"True"<<endl;
	}else
		cout << "False" <<endl;
*/
	showSortedOutput(arr, asize);
	sortStrings(arr, asize);
	showSortedOutput(arr, asize);

	//return 0
	return (0);
}

