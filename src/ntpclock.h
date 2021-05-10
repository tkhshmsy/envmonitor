#ifndef __NTPCLOCK__
#define __NTPCLOCK__

#include <time.h>

class NTPClock
{
public:
    NTPClock();
    ~NTPClock();

    bool setup();
    bool sync();
    bool getTime(struct tm *timeinfo);
};


#endif //__NTPCLOCK__
