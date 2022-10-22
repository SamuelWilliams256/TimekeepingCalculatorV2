#include "Time.h"

Time::Time() :
    _hours(-1),
    _minutes(-1)
{
}

Time::Time(int hours, int minutes) :
    _hours(hours),
    _minutes(minutes)
{
}

void Time::setTime(int hours, int minutes)
{
    _hours = hours;
    _minutes = minutes;
}

void Time::setHours(int hours)
{
    _hours = hours;
}

void Time::setMinutes(int minutes)
{
    _minutes = minutes;
}

int Time::getHours() const
{
    return _hours;
}

int Time::getMinutes() const
{
    return _minutes;
}

std::string Time::getTwelveHourFormatString() const
{
    std::string amOrPm = (_hours < 12) ? "am" : "pm";

    int formattedHours = _hours;
    if (formattedHours > 12)
    {
        formattedHours -= 12;
    }
    else if (formattedHours == 0)
    {
        formattedHours = 12;
    }

    std::string formattedMinutes = std::to_string(_minutes);
    if (formattedMinutes.length() == 1)
    {
        formattedMinutes = "0" + formattedMinutes;
    }

    std::string twelveHourFormatString = std::to_string(formattedHours)
                                       + ":"
                                       + formattedMinutes
                                       + amOrPm;
    return twelveHourFormatString;
}

