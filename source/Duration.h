#ifndef DURATION_H
#define DURATION_H

#include "Time.h"

class Duration
{
public:
    Duration(const Time &startTime, const Time &endTime);

    double getDurationHours() const;
    Time getStartTime() const;
    Time getEndTime() const;

private:
    const Time _startTime;
    const Time _endTime;
};

#endif

