#ifndef TIME_H
#define TIME_H

#include <string>

//Uses military time format
class Time
{
public:
    Time();
    Time(int hours, int minutes);

    void setTime(int hours, int minutes);
    void setHours(int hours);
    void setMinutes(int minutes);

    int getHours() const;
    int getMinutes() const;
    std::string getTwelveHourFormatString() const;

private:
    int _hours;
    int _minutes;
};

#endif

