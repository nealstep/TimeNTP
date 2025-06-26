#ifndef BASE_H
#define BASE_H

#include <Arduino.h>

class TimeNTP {
   public:
    TimeNTP(const char *ntpServer, const char *timeZone);
    void wait(void);
    char *getTime(void);
private:
    const char *server;
    const char *tz;
};

#endif  // BASE_H