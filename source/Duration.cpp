#include "Duration.h"

Duration::Duration(const Time& startTime, const Time& endTime) :
    _startTime(startTime),
    _endTime(endTime)
{
}

double Duration::getDurationHours() const
{
    int differenceHours = _endTime.getHours() - _startTime.getHours();
    int differenceMinutes = _endTime.getMinutes() - _startTime.getMinutes();

    if (differenceMinutes < 0)
    {
        differenceHours--;
        differenceMinutes += 60;
    }
    if (differenceHours < 0)
    {
        differenceHours += 24;
    }

    return((double)differenceHours + ((double)differenceMinutes / 60.0));
}

Time Duration::getStartTime() const
{
    return _startTime;
}

Time Duration::getEndTime() const
{
    return _endTime;
}

