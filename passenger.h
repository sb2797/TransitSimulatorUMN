/**
 * @file passenger.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_

#include <iostream>
#include <string>

class Passenger {  // : public Reporter {
 public:
   /**
       * @brief Constructs a passenger with a standard name and id.
       *
       *
       * @param[in] int holding an id number
       * @param[in] string holding a name of a created passenger.
       *
       */
  explicit Passenger(int = -1, std::string = "Nobody");
  /**
  * @brief update passengers time at stop and time on bus
  */
  void Update();
  /**
  * @brief check if passengers are not on bus then get them on bus
  */
  void GetOnBus();
  /**
  * @brief get passenger total wait time to get to destination.
  * This include time on bus and time waited at stop
  *
  * @return integer
  */
  int GetTotalWait() const;
  /**
  * @brief check if passenger is on bus
  *
  * @return boolean
  */
  bool IsOnBus() const;
  /**
  * @brief get the passenger destination stop id
  *
  * @return integer
  */
  int GetDestination() const;
  /**
  * @brief get passenger time waited at stop
  *
  * @return integer.
  */
  void Report(std::ostream&) const;
 private:
  std::string name_;
  int destination_stop_id_;
  int wait_at_stop_;
  int time_on_bus_;
  int id_;
  static int count_;  // global count, used to set ID for new instances
};
#endif  // SRC_PASSENGER_H_
