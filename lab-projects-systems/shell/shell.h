#ifndef shell_h
#define shell_h

#define debug 1

#ifdef debug 
#define dprintf printf 
#else
#define dprintf(...)
#endif

#endif
