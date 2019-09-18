#ifndef shell_h
#define shell_h

#define debug 0

#ifdef debug 
#define dprintf printf 
#else
#define dprintf(...)
#endif

#endif
