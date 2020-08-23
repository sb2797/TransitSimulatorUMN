/**
 * @file passenger_unloader.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/passenger_unloader.h"
// #include <string>
// #include <sstream>

int PassengerUnloader::UnloadPassengers(std::list<Passenger *>& passengers,
                                        Stop * current_stop) {
  // TODO(wendt): may need to do end-of-life here
  // instead of in Passenger or Simulator
  int passengers_unloaded = 0;
  for (std::list<Passenger *>::iterator it = passengers.begin();
      it != passengers.end();
      it++) {
    (*it)->Report(mystream);
    std::vector<std::string> data_vector = myUtil->processOutput(mystream);
    FileWriter* other_writer = myWriter->getInstance();
    other_writer->Write(passenger_file_name, data_vector);
    if ((*it)->GetDestination() == current_stop->GetId()) {
      // could be used to inform scheduler of end-of-life?
      // This could be a destructor issue as well.
      // *it->FinalUpdate();
      it = passengers.erase(it);
      // getting seg faults, probably due to reference deleted objects
      // here
      it--;
      passengers_unloaded++;
    }
  }

  return passengers_unloaded;
}
