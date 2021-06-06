#ifndef CHARGECODE_H
#define CHARGECODE_H

#include <string>

class ChargeCode
{
public:
    ChargeCode(const std::string &alias, const std::string &chargeNumber);
    std::string getAlias() const;
    std::string getChargeNumber() const;

private:
    const std::string _alias;
    const std::string _chargeNumber;
};

#endif

