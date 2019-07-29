
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
const char *CString::cstring() const {
	return cstring_;
}
bool CString::operator<(const CString &cstringarg){
	int result = cmp( cstring_, cstringarg.cstring());
	//cout <<cstring_<<"< "<< cstringarg.cstring()<<" "  <<result<<endl;
	
	if ( ( result % 32 ) == 0 ) {
		if( result > 0 ) {
			return true;
		}	
	}
	else if ( result < 0  ) {
		return true;
	}

	return false;
}

int CString::cmp(const char *cstring_1, const char *cstring_2){

	while( *cstring_1 && *cstring_2 ){
		if( *cstring_1 == *cstring_2 ){
			cstring_1++;
			cstring_2++;
			continue;
		}else{
			return (*cstring_1 - *cstring_2);
		}
	}

	return 0;
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




