#include "TimeNTP.h"

#if defined(ESP8266)
uint32_t sntp_startup_delay_MS_rfc_not_less_than_60000() {
    randomSeed(A0);
    return random(5000);
}
#endif  // ESP8266

TimeNTP::TimeNTP(const char *ntpServer, const char *timeZone) {
    server = ntpServer;
    tz = timeZone;
}

void TimeNTP::wait(void) {
#if defined(ESP8266)
    configTime(tz, server);
#elif defined(ESP32)
    configTime(0, 0, server);
    setenv("TZ", tz, 1);
#endif  // ESP
    tzset();
    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2) {
        delay(500);
        now = time(nullptr);
    }
}

char *TimeNTP::getTime(void) {
    time_t now = time(nullptr);
    struct tm timeinfo;

    localtime_r(&now, &timeinfo);
    return asctime(&timeinfo);
}
