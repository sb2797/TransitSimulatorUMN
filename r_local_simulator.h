/**
 * @file r_local_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_LOCAL_SIMULATOR_H_
#define SRC_LOCAL_SIMULATOR_H_
#include <vector>
#include <string>
#include "src/simulator.h"
/**
 * @brief the main class for my Regression Test driver
 *
 * This is a shorter hardcoded set of stops and routes used for
 * my regression testing, otherwise it functions identically to
 * r_local_simulator. Based to local_simulator.
 *
 */
class rLocalSimulator : public Simulator {
 public:
  bool Start() override;
  bool Update() override;
 private:
  std::vector<int> bus_counters_;
  std::vector<int> bus_start_timings_;
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
};

#endif  // SRC_LOCAL_SIMULATOR_H_
