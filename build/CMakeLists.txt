cmake_minimum_required(VERSION 3.5)
project(TimekeepingCalculator)
add_executable(timekeeping_calculator 
   ../source/ChargeCode.cpp 
   ../source/Time.cpp 
   ../source/Duration.cpp 
   ../source/ChargeCodeEntry.cpp 
   ../source/TimeLogger.cpp 
   ../source/Main.cpp)
