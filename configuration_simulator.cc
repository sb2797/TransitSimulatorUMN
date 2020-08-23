/**
 * @file local_simulator.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * Edited by: Srivatsan Balaji
 */
#include "src/configuration_simulator.h"

#include <vector>
#include <list>

#include "src/bus.h"
#include "src/stop.h"
#include "src/route.h"
#include "src/random_passenger_generator.h"

ConfigurationSimulator::ConfigurationSimulator(ConfigManager* config_m) {
  config_manager_ = config_m;
}


// This is heavily built from visualization_simulator and local_simulator
bool ConfigurationSimulator::Start(const std::vector<int>& bus_start_timings,
   const int& num_time_steps) {
  bus_start_timings_ = bus_start_timings;
  num_time_steps_ = num_time_steps;


  time_since_last_bus_generation_.resize(bus_start_timings_.size());
  for (int i = 0; i < static_cast<int>(time_since_last_bus_generation_.size());
  i++) {
      time_since_last_bus_generation_[i] = 0;
  }
  // by default makes an array of len 1 with a 0 in it { 0 }

  simulation_time_elapsed_ = 0;  // init, but also allows restart

  prototype_routes_ = config_manager_->GetRoutes();
  for (int i = 0; i < static_cast<int>(prototype_routes_.size()); i++) {
    // Removed Iter2 Refactor from here.
    prototype_routes_[i]->Report(std::cout);
  }

  // bus counters is the naming convention of the buses,
  // first name starts at 10001
  bus_counters_.push_back(10000);

  // This will eventually be replaced by configuration/command line argument
  bus_start_timings_.push_back(10);
  return true;
}

// This is heavily built from visualization_simulator and local_simulator
bool ConfigurationSimulator::Update() {
  // increase time
  simulation_time_elapsed_++;

  std::cout << "~~~~~~~~~~~ The time is now " << simulation_time_elapsed_;
  std::cout << " ~~~~~~~~~~~" << std::endl;

  // various route-indexed list iterators
  std::vector<int>::iterator bus_gen_timing_iter = bus_start_timings_.begin();
  std::vector<int>::iterator bus_counter_iter = bus_counters_.begin();
  std::vector<Route *>::iterator prototype_route_iter =
                                                     prototype_routes_.begin();

  // increase each time since last bus
  // various iterators parallel the time_since_last iterator
  for (std::vector<int>::iterator it = time_since_last_bus_generation_.begin();
      it != time_since_last_bus_generation_.end();
      it++, bus_gen_timing_iter++, bus_counter_iter++) {
    (*it)++;

    // if time since last [index] == bus gen timing[index]
    if (0 >= (*bus_gen_timing_iter)) {
      // create a new bus! routes are:
      Route * outbound = (*prototype_route_iter);
      prototype_route_iter++;
      Route * inbound = (*prototype_route_iter);
      prototype_route_iter++;

      active_buses_.push_back(new Bus(std::to_string((*bus_counter_iter)),
                                  outbound->Clone(), inbound->Clone(), 60, 1));
      (*bus_counter_iter)++;
      (*bus_gen_timing_iter) = 10;
    } else {
      prototype_route_iter++;
      prototype_route_iter++;
      (*bus_gen_timing_iter)--;
    }
  }

  // for each bus
  for (std::list<Bus *>::iterator bus_iter = active_buses_.begin();
      bus_iter != active_buses_.end(); bus_iter++) {
    // update bus
    (*bus_iter)->Update();
    if ((*bus_iter)->IsTripComplete()) {
      bus_iter = active_buses_.erase(bus_iter);
      bus_iter--;
    } else {
      // only report if the bus still exists,
      (*bus_iter)->Report(std::cout);
    }
  }

  // for each stop
  for (std::vector<Route *>::iterator route_iter = prototype_routes_.begin();
      route_iter != prototype_routes_.end(); route_iter++) {
    // update stop
    (*route_iter)->Update();
    (*route_iter)->Report(std::cout);
  }
  return true;
}
