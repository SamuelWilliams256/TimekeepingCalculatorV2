#include "TimeLogger.h"

#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <string>

namespace //Anonymous namespace
{
    std::vector<ChargeCode> parseChargeCodeListFromConfig(const std::string &filename)
    {
        std::ifstream config(filename);
        if (config.fail())
        {
            std::string errorMessage = "Could not locate file: " + filename;
            throw std::runtime_error(errorMessage.c_str());
        }

        std::vector<ChargeCode> chargeCodeList;
        while (config.eof() == false)
        {
            std::string chargeCodeAlias;
            std::string chargeCodeNumber;

            config >> chargeCodeAlias;
            config >> chargeCodeNumber;
            chargeCodeList.push_back(ChargeCode(chargeCodeAlias, chargeCodeNumber));
        }

        config.close();
        return chargeCodeList;
    }

    //Returns true if timeString has a valid syntax and could be parsed. Returns false otherwise.
    bool parseTimeFromString(const std::string &timeString, Time &resultTime)
    {
        std::string lowercaseTimeString;
        for (int i = 0; i < timeString.length(); i++)
        {
            lowercaseTimeString += std::tolower(timeString[i]);
        }

        //e.g. "22:13", "0100", or "12:41"
        const std::regex militaryTimeRegex("^([01]?\\d|2[0-3]):?([0-5]\\d)$");

        //e.g. "12:30 am", "1:11pm", or "259am"
        const std::regex twelveHourTimeRegex("^(0?[1-9]|1[0-2]):?[0-5]\\d ?(a|p)m?$");

        //e.g. "5 am", "12a", "10pm", "3 p"
        const std::regex shorthandTimeRegex("^((1[0-2])|([1-9])) ?(a|p)m?$");

        if (std::regex_match(lowercaseTimeString, militaryTimeRegex))
        {
            std::smatch hoursStringMatch;
            const std::regex hoursRegex("^\\d?\\d(?=(:?\\d\\d))");
            std::regex_search(lowercaseTimeString, hoursStringMatch, hoursRegex);
            resultTime.setHours(std::stoi(hoursStringMatch[0]));

            std::smatch minutesStringMatch;
            const std::regex minutesRegex("\\d\\d$");
            std::regex_search(lowercaseTimeString, minutesStringMatch, minutesRegex);
            resultTime.setMinutes(std::stoi(minutesStringMatch[0]));

            return true;
        }

        if (std::regex_match(lowercaseTimeString, twelveHourTimeRegex))
        {
            std::smatch hoursStringMatch;
            const std::regex hoursRegex("^(\\d\\d(?=:?\\d\\d))|^(\\d(?=:?\\d\\d(?= |a|p)))");
            std::regex_search(lowercaseTimeString, hoursStringMatch, hoursRegex);
            int hours = std::stoi(hoursStringMatch[0]);

            //Convert to military time
            if (hours == 12)
            {
                hours -= 12;
            }
            if (lowercaseTimeString.find("a") == std::string::npos)
            {
                hours += 12;
            }
            resultTime.setHours(hours);

            std::smatch minutesStringMatch;
            const std::regex minutesRegex("\\d\\d(?= ?(?=(a|p)m?$))");
            std::regex_search(lowercaseTimeString, minutesStringMatch, minutesRegex);
            resultTime.setMinutes(std::stoi(minutesStringMatch[0]));

            return true;
        }

        if (std::regex_match(lowercaseTimeString, shorthandTimeRegex))
        {
            std::smatch hoursStringMatch;
            const std::regex hoursRegex("^\\d?\\d");
            std::regex_search(lowercaseTimeString, hoursStringMatch, hoursRegex);
            int hours = std::stoi(hoursStringMatch[0]);

            //Convert to military time format
            if (hours == 12)
            {
                hours -= 12;
            }
            if (lowercaseTimeString.find("a") == std::string::npos)
            {
                hours += 12;
            }
            resultTime.setTime(hours, 0);
            return true;
        }

        return false;
    }

    ChargeCode getChargeCodeFromUser(const std::vector<ChargeCode> &listOfChargeCodes)
    {
        std::cout << "Charge Codes:\n";

        for (int i = 0; i < listOfChargeCodes.size(); i++)
        {
            std::cout << std::to_string(i + 1) << ") " << listOfChargeCodes[i].getAlias();
            std::cout << ": " << listOfChargeCodes[i].getChargeNumber() << "\n";
        }

        std::cout << "\nEnter the number of the charge code that you would like to make an entry for: ";
        std::string entryNumber;
        std::getline(std::cin, entryNumber);

        int chargeCodeIndex = std::stoi(entryNumber) - 1;
        while (chargeCodeIndex >= listOfChargeCodes.size() || chargeCodeIndex < 0)
        {
            std::cout << "Invalid charge code selection. Try again: ";
            std::getline(std::cin, entryNumber);
            chargeCodeIndex = std::stoi(entryNumber) - 1;
        }

        return listOfChargeCodes[chargeCodeIndex];
    }

    Time getTimeFromUser(const std::string &prompt)
    {
        std::cout << prompt;
        std::string timeString;
        std::getline(std::cin, timeString);

        Time time;
        bool gotValidTimeFromUser = parseTimeFromString(timeString, time);

        while (!gotValidTimeFromUser)
        {
            std::cout << "Failed to parse time string. Try again: ";
            std::getline(std::cin, timeString);
            gotValidTimeFromUser = parseTimeFromString(timeString, time);
        }

        return time;
    }

}

TimeLogger::TimeLogger(const std::string &chargeCodeListFilename) :
    _listOfAvailableChargeCodes(parseChargeCodeListFromConfig(chargeCodeListFilename))
{
}

void TimeLogger::execute()
{
    const ChargeCode chargeCode = getChargeCodeFromUser(_listOfAvailableChargeCodes);

    const Time startTime = getTimeFromUser("Enter the start time for " + chargeCode.getAlias() + ": ");
    const Time endTime = getTimeFromUser("Enter the end time for " + chargeCode.getAlias() + ": ");
    const Duration duration(startTime, endTime);

    _entryList.push_back(ChargeCodeEntry(chargeCode, duration));
    displayEntryList();
}

void TimeLogger::displayEntryList() const
{
    const std::function <double(double)> roundToHundredths = [](const double &valueToRound)
    {
        return std::round(valueToRound * 100) / 100;
    };

    std::cout << "Your entries:\n";
    double totalHours = 0;
    for (int i = 0; i < _entryList.size(); i++)
    {
        const double roundedDuration = roundToHundredths(_entryList[i].getDuration().getDurationHours());
        totalHours += roundedDuration;

        std::cout << _entryList[i].getChargeCode().getChargeNumber()
            << " (" << _entryList[i].getChargeCode().getAlias() << "): " << roundedDuration << " hours"
            << " [" << _entryList[i].getDuration().getStartTime().getTwelveHourFormatString() << " - "
            << _entryList[i].getDuration().getEndTime().getTwelveHourFormatString() << "]\n";
    }

    std::cout << "Total Hours: " << totalHours << "\n\n";
}
