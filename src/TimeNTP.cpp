#include "TimeNTP.h"

uint32_t sntp_startup_delay_MS_rfc_not_less_than_60000() {
    randomSeed(A0);
    return random(5000);
}

TimeNTP::TimeNTP(const char *ntpServer, const char *timeZone) {
    configTime(timeZone, ntpServer);
}

void TimeNTP::wait(void) {
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
