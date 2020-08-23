/**
 * @file configuration_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * @edited By Srivatsan Balaji
 */
#ifndef SRC_CONFIGURATION_SIMULATOR_H_
#define SRC_CONFIGURATION_SIMULATOR_H_

#include <vector>
#include <list>
#include "src/bus.h"
#include "src/route.h"
#include "src/config_manager.h"


/**
 * @brief The Simulator used for config_sim.
 */
class ConfigurationSimulator {
 public:
  /*
   * @brief The explicit constructor for ConfigurationSimulator.
   * @param[in] ConfigManager*, A pointer to a ConfigManager in order
   * to organize the configuration correctly.
   *
   * @return A ConfigurationSimulator object.
   */
  explicit ConfigurationSimulator(ConfigManager *);
  /*
   * @brief Initializes the ConfigurationSimulator
   * @param[in] std::vector<int>&, a list of bus start timings
   * @param[in] const int&, the number of time-steps that the sim will run for.
   *
   * @return True if successful, false otherwise.
   */
  bool Start(const std::vector<int>&, const int&);
  /*
   * @brief Updates info in sim, called num_time_steps_ times.
   *
   * @return True if successful, false otherwise.
   */
  bool Update();

 private:
  ConfigManager* config_manager_;
  std::vector<int> bus_counters_;
  std::vector<int> bus_start_timings_;
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
  int num_time_steps_;

 protected:
  std::vector<double *> distance_between_sets_;
  std::vector<PassengerGenerator *> passenger_generators_;
  std::vector<Route *> prototype_routes_;
  std::list<Bus *> active_buses_;         // buses leave scope
  std::list<Stop *> all_stops_;
};

#endif  // SRC_CONFIGURATION_SIMULATOR_H_
