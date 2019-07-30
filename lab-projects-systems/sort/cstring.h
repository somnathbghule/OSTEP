#ifndef CSTRING_H
#define CSTRING_H

#include <iostream>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>

using namespace std;

class CString {
	public:
		CString(const char *cstring);
		int len();
		void show();
		bool operator<(const CString &cstring);
		const char *cstring() const;
	private:
		CString();
		int len(const char *cstring);
		bool copy(char *cstring, const char *cstringdest);
		int  cmp(const char *cstring_1, const char *cstring_2);
		char *cstring_;
};


#endif
