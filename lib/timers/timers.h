#ifndef timers_h
#define timers_h

typedef unsigned long (*nowMillisProc)();

nowMillisProc defaultNowMillisProc();

#endif