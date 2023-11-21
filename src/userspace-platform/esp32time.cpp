#include "ESP32Time.h"
#include <ctime>

ESP32Time::ESP32Time(int) {}

static std::time_t ttime;

// nasty function returns pointer to static space...
std::tm *const now() {
	ttime = std::time(nullptr);
	return std::localtime(&ttime);
}


int ESP32Time::getYear() { return now()->tm_year; }
int ESP32Time::getMonth() { return now()->tm_mon; }
int ESP32Time::getDay() { return now()->tm_mday; }
int ESP32Time::getDayofWeek() { return now()->tm_wday; }
int ESP32Time::getDayofYear() { return now()->tm_yday; }
int ESP32Time::getHour(bool) { return now()->tm_hour; }
int ESP32Time::getMinute() { return now()->tm_min; }
int ESP32Time::getSecond() { return now()->tm_sec; }
void ESP32Time::setTime(int, int, int, int, int, int) {}

