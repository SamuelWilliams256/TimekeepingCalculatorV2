#ifndef TIMELOGGER_H
#define TIMELOGGER_H

#include "ChargeCode.h"
#include "ChargeCodeEntry.h"

#include <vector>

class TimeLogger
{
public:
    TimeLogger(const std::string &chargeCodeListFilename);
    void execute();

private:
    void displayEntryList() const;

    const std::vector<ChargeCode> _listOfAvailableChargeCodes;
    std::vector<ChargeCodeEntry> _entryList;
};

#endif
