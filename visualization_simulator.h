/**
 * @file visualization_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef VISUALIZATION_SIMULATOR_H_
#define VISUALIZATION_SIMULATOR_H_

#include <vector>
#include <list>
#include "web_interface.h"
#include "config_manager.h"
#include "src/FileWriterManager.h"
#include "src/Util.h"

class Route;
class Bus;
class Stop;

class VisualizationSimulator {
 public:
        VisualizationSimulator(WebInterface*, ConfigManager*, std::ostream*);
        ~VisualizationSimulator();

        void Start(const std::vector<int>&, const int&);
        bool Update();
        bool CanUpdate();
        void TogglePause();
        void ClearBusListeners();
        void ClearStopListeners();
        void AddBusListener(std::string * id, IObserver<BusData*> * observer);
        void AddStopListener(std::string * id, IObserver<StopData*> * observer);

 private:
        void ExecuteUpdate();
        WebInterface* webInterface_;
        ConfigManager* configManager_;

        std::vector<int> busStartTimings_;
        std::vector<int> timeSinceLastBus_;
        int numTimeSteps_;
        int simulationTimeElapsed_;

        std::vector<Route *> prototypeRoutes_;
        std::vector<Bus *> busses_;

        int busId = 1000;
        bool paused_;
        std::ostream* out_;
        std::ostringstream mystream;
        std::string bus_stats_file_name = "BusData.csv";
        Util* myUtil = new Util();
        File_Writer_Manager* myWriter = new File_Writer_Manager();
};

#endif // VISUALIZATION_SIMULATOR_H_
