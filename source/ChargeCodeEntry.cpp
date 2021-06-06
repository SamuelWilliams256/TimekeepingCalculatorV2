#include "ChargeCodeEntry.h"

ChargeCodeEntry::ChargeCodeEntry(const ChargeCode &chargeCode, const Duration &duration) :
    _chargeCode(chargeCode),
    _duration(duration)
{
}

ChargeCode ChargeCodeEntry::getChargeCode() const
{
    return _chargeCode;
}

Duration ChargeCodeEntry::getDuration() const
{
    return _duration;
}

