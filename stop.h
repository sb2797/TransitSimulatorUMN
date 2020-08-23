/**
 * @file Bus.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_STOP_H_
#define SRC_STOP_H_

#include <list>
#include <iostream>

#include "src/bus.h"
#include "src/passenger.h"

class Bus;

class Stop : public IObservable<StopData*>{
 public:
   /**
   * @brief Constructs a stop with a id number, longitude, and latitude.
   *
   *
   * @param[in] int holding an stop id number
   * @param[in] double holding a stop longitude
   * @param[in] double holding a stop latitude
   *
   */
  explicit Stop(int, double = 44.973723, double = -93.235365);

  /**
  * @brief Get stop id number
  *
  * @return integer
  */
  int LoadPassengers(Bus *);  // Removing passengers from stop
  // and onto a bus
  /**
  * @brief Load and count passengers in a stop list onto bus
  *
  * @param[in] Bus pointer pointing at Bus class
  *
  * @return integer
  */
  int AddPassengers(Passenger *);  // Adding passengers
  // to the stop (from the generator)
  /**
  * @brief Add passengers into the stop passengers list and return 1
  *
  * @param[in] Passenger pointer pointing at passenger
  *
  * @return integer
  */
  void Update();
  /**
  * @brief print stops status as well as pasenger status at that stop
  */
  int GetId() const;
  /**
  * @brief Get stop id number
  *
  * @return integer
  */
  void Report(std::ostream&) const;

  void Update2();
  void UpdateStopData();
  StopData GetStopData() const;

  // Vis Getters
  double GetLongitude() const { return longitude_; }
  double GetLatitude() const { return latitude_; }
  size_t GetNumPassengersPresent() { return passengers_.size(); }

 private:
  int id_;
  std::list<Passenger *> passengers_;  // considered array, vector, queue, list
  double longitude_;
  double latitude_;  // are we using long/lat coords?
  StopData stop_data_;
  // derived information - not needed depending on passengers_
  // data structure implementation?
  // int passengers_present_;
};
#endif  // SRC_STOP_H_
