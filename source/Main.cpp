#include "TimeLogger.h"

#include <iostream>
#include <string>

bool userWantsToContinue()
{
    std::cout << "Would you like to continue? (y/n): ";

    std::string usersResponse;
    std::getline(std::cin, usersResponse);
    while (usersResponse != "y" && usersResponse != "n")
    {
        std::cout << "Please enter \"y\" or \"n\": ";
        std::getline(std::cin, usersResponse);
    }

    if (usersResponse == "y")
    {
        return true;
    }
    return false;
}

int main()
{
    try
    {
        TimeLogger timeLogger("ChargeCodes.txt");

        do
        {
            timeLogger.execute();
        } while (userWantsToContinue());

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception thrown: " << e.what() << "\n";
        std::cerr << "The program will now terminate.\n";
        return 1;
    }
}

