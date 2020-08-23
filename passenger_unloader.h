/**
 * @file passenger_unloader.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_PASSENGER_UNLOADER_H_
#define SRC_PASSENGER_UNLOADER_H_
#include <list>
#include "src/passenger.h"
#include "src/stop.h"
#include "src/FileWriterManager.h"
#include "src/Util.h"

class Stop;
class Passenger;

class PassengerUnloader {
 public:
  // UnloadPassengers returns the number of passengers removed from the bus.
  int UnloadPassengers(std::list<Passenger*>& passengers, Stop * current_stop);

private:
    std::string passenger_file_name = "PassData.csv";
    std::ostringstream mystream;
    Util* myUtil = new Util();
    File_Writer_Manager* myWriter = new File_Writer_Manager();
};
#endif  // SRC_PASSENGER_UNLOADER_H_
