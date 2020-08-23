/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_BUS_H
#define SRC_BUS_TYPES_H

#include <iostream>
#include <list>
#include <string>
#include "src/data_structs.h"
#include "src/IObservable.h"
#include "src/passenger.h"
#include "src/passenger_loader.h"
#include "src/passenger_unloader.h"
#include "src/route.h"
#include "src/stop.h"

class PassengerUnloader;
class PassengerLoader;
class Route;
class Stop;

class Bus : public IObservable<BusData*> {
 public:
  Bus(std::string name, Route * out, Route * in, int capacity = 60,
                double speed = 1, std::string type = "Medium");
  /**
   * @brief Get passengers on bus
   *
   * @return boolean
  */
  bool IsTripComplete();
  /**
  * @brief check if bus is current at incoming or outgoing route
  *
  * @return route
  */
  bool LoadPassenger(Passenger *);  // returning revenue delta
  /**
  * @brief Get passengers off the bus with they reach their destination
  *
  * @return integer
  */
  bool Move();
  /**
  * @brief check if bus has complete its outgoing and incoming route
  *
  * @return boolean
  */
  void Update();
  /**
  * @brief Print bus information and status
  */
  void Report(std::ostream&);
  /**
  * @brief Print bus information and status
  * called by the visualizer to instruct
  * the bus object to populate the BusData
  * struct with the latest information
  * (see the file data_structs.h to
  * determine what information the BusData
  * struct stores.). This a nontivial
  * method, so we will outline its operation
  * (which you have to implement), below.
  */
  // Vis Getters
  void UpdateBusData();
  /**
  * @brief called by the visualizer to get then
  * name of the bus
  */
  BusData GetBusData() const;
  /**
  * @brief called by the visualizer to get then
  * name of the bus
  */
  std::string GetName() const { return name_; }
  /**
  * @brief called by the visualizer to get the pointer
  * to the bus's next stop
  */
  Stop * GetNextStop() const { return next_stop_; }
  /**
  * @brief called by the visualizer to get the current
  * number of passengers on the bus
  */
  size_t GetNumPassengers() const { return passengers_.size(); }
  /**
  * @brief called by the visualizer to get the current
  * number of passengers on the bus
  */
  int GetCapacity() const { return passenger_max_capacity_; }

 private:
  int UnloadPassengers();  // returning revenue delta
  int HandleBusStop();
  void ToNextStop();
  double UpdateDistance();
  Route* CurrentRoute();
  // bool Refuel();
  PassengerUnloader * unloader_;
  PassengerLoader * loader_;
  std::list<Passenger *> passengers_;
  int passenger_max_capacity_;
  // double revenue_; // revenue collected from passengers, doesn't include
                      // passengers who pay on deboard
  // double fuel_;   // may not be necessary for our simulation
  // double max_fuel_;
  std::string name_;
  std::string type_;
  double speed_;  // could also be called "distance travelled in one time step"
  Route * outgoing_route_;
  Route * incoming_route_;
  double distance_remaining_;  // when negative?, unload/load procedure occurs
                              // AND next stop set
  Stop * next_stop_;
  // bool trip_complete_;  // [DERIVED data] when BOTH routes are at end, trip
  // is complete

  // Vis data for bus
  BusData bus_data_;

  protected:
    int total_passengers;
};
#endif  // SRC_BUS_H_
