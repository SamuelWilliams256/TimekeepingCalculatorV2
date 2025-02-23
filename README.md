# OVERVIEW

This timekeeping calculator is a command-line program that will read from a file in the directory in which the program is run called `ChargeCodes.txt`. It will use this file to generate a list of available charge codes and an alias for each. It will then walk you through calculating a duration worked for each charge code given a start time and an end time.

The format of `Chargecodes.txt` is expected to be:

```
<ChargeCodeAlias1> <ChargeCodeNumber1>
<ChargeCodeAlias2> <ChargeCodeNumber2>
<ChargeCodeAlias3> <ChargeCodeNumber3>
```
...etc. where `<ChargeCodeAlias>` is a name given to a particular charge code. This list is customizeable and extensible, so long as each alias has a charge code associated with it.

# COMPILING

Navigate to the build directory and run CMake in it to generate a make file or solution of the desired type. Then use the makefile/solution to build the executable.

e.g.) `cd build; cmake ../source; make`
