#include "ChargeCode.h"

ChargeCode::ChargeCode(const std::string& alias, const std::string& chargeNumber):
    _alias(alias),
    _chargeNumber(chargeNumber)
{
}

std::string ChargeCode::getAlias() const
{
    return _alias;
}

std::string ChargeCode::getChargeNumber() const
{
    return _chargeNumber;
}

