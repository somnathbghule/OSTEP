
#include <cstring.h>
CString::CString(){
	cstring_ = NULL;
}

int CString::len(){
	return len(cstring_);
}

int CString::len( const char * cstring){
	int tlen=0;
	while(*cstring++)
		tlen++;
	return tlen;
}

bool CString::copy(char *cstring, const char *cstringdest){
	while( *cstringdest )
		*cstring++=*cstringdest++;
	return true;
}

void CString::show(){
	cout<<cstring_<<endl;
}

CString::CString( const char *cstring ){
	int tlen=len(cstring);
        cstring_ = new char [tlen];
	copy(cstring_, cstring);
}




