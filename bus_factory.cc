/*
* Copyright 3081. All rights reserved
* @author Srivatsan Balaji
*/

#include "src/bus_factory.h"
#include <ctime>
#include <iostream>

Bus* BusFactory::Generate(std::string name) {
  static int strat_one_counter = 0;
  static int strat_two_counter = 0;
  static int strat_three_counter = 0;
  int bus_type = 0;

    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    std::cout << "The time is currently: "<< now->tm_hour<< endl;
     if (now->tm_hour >= 6 && now->tm_hour < 8) {
      std::cout << "USING DEPLOYMENT STRATEGY 1"<< endl;
      std::cout << "STRAT 1 COUNTER: "<< strat_one_counter << endl;
      if (strat_one_counter == 0) {
        bus_type = 1;
        strat_one_counter = 1;
      }
      else {
        bus_type = 2;
        strat_one_counter = 0;
      }
    }
    else if (now->tm_hour >= 8 && now->tm_hour < 15) {
      std::cout << "USING DEPLOYMENT STRATEGY 2" << endl;
      std::cout << "STRAT 2 COUNTER: " << strat_two_counter << endl;
      if (strat_two_counter == 0) {
        std::cout << "Setting to Medium" << endl;
        bus_type = 2;
        strat_two_counter = 1;
      }
      else {
        std::cout << "Setting to Large" << endl;
        bus_type = 3;
        strat_two_counter = 0;
      }
    }

    else if(now->tm_hour >= 15 && now->tm_hour < 20) {
      std::cout << "USING DEPLOYMENT STRATEGY 3" << endl;
      std::cout << "STRAT 3 COUNTER: " << strat_three_counter << endl;
      if(strat_three_counter % 3 == 0) {
        std::cout << "Setting to Small" << endl;
        bus_type = 1;
        std::cout << "type succesfully changed" << endl;
      }
      else if(strat_three_counter % 3 == 1){
        std::cout << "Setting to Medium" << endl;
        bus_type = 2;
      }
      else{
        std::cout << "Setting to Large" << endl;
        bus_type = 3;
      }
      std::cout << "Incrementing counter" << endl;
      strat_three_counter++;
      std::cout << "counter succesfully incremented" << endl;
    }

    else {
      std::cout << "SMALL" << endl;
      bus_type = 1;
    }


    if(bus_type == 1) {
      std::cout << "returning small bus" << endl;
        return new SmallBus(name, outbound_, inbound_, speed_);
    } else if (bus_type == 2) {
      std::cout << "returning medium bus" << endl;
        return new MediumBus(name, outbound_, inbound_, speed_);
    } else if (bus_type == 3) {
      std::cout << "returning large bus" << endl;
        return new LargeBus(name, outbound_, inbound_, speed_);
    } else {
        std::cout << "type_: " << type_ << std::endl;
        throw "Type must be small, medium or large";
    }
}
