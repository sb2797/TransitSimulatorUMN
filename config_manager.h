/*
* Copyright 3081. All rights reserved
* @author Srivatsan Balaji
*/

#ifndef SRC_CONFIG_MANAGER_H_
#define SRC_CONFIG_MANAGER_H_

#include <vector>
#include <string>
/**
 * @brief A class for reading config.txt files and getting their data
 *
 * A class used by my_local_sim to read in route and stop data
 * from txt files so that they dont need to be hard coded
 * and mutliple sets can exist to test
 */

class Route;
class ConfigManager {
 public:
   /**
   * @brief Constructs a Configuration Manager
   */
        ConfigManager();
        /**
        * @brief deconstructs configuration manager.
        */
        ~ConfigManager();
        /**
        * @brief Read configuration file and set up
        * bus, routes, stops, and passengers
        *
        * @param[in] string holding a config filename.
        */  
        void ReadConfig(const std::string filename);
        /**
        * @brief ReadConfig
        *
        * @param[in] string for filename and location to be read
        * Given a file name it goes through the file and translates
        * the information in it to a list of routes. Files must be of the
        * correct format to get the information.
        */
        std::vector<Route *> GetRoutes() const { return routes; }
        /**
        * @brief GetRoutes
        *
        * *return std::vector<Route *> of routes it has read in from file.
        *
        */
 private:
        std::vector<Route *> routes;
};

#endif  // SRC_CONFIG_MANAGER_H_
