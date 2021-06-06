#ifndef CHARGECODEENTRY_H
#define CHARGECODEENTRY_H

#include "ChargeCode.h"
#include "Duration.h"
class ChargeCodeEntry
{
public:
    ChargeCodeEntry(const ChargeCode &chargeCode, const Duration &duration);

    ChargeCode getChargeCode() const;
    Duration getDuration() const;

private:
    const ChargeCode _chargeCode;
    const Duration _duration;
};

#endif

