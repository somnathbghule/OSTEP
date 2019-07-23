#ifndef CSTRING_H
#define CSTRING_H

#include <iostream>
using namespace std;

class CString {
	public:
		CString(const char *cstring);
		int len();
		void show();
	private:
		CString();
		int len(const char *cstring);
		bool copy(char *cstring, const char *cstringdest);
		char *cstring_;
};


#endif
