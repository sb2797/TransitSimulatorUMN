/*
* Copyright 3081. All rights reserved
* @author Srivatsan Balaji
*/
#ifndef SRC_BUS_FACTORY_H_
#define SRC_BUS_FACTORY_H_

#include "./bus.h"
#include "./bus_types.h"
#include <string>

class BusFactory {
 public:
    BusFactory(std::string type, Route* outbound, Route* inbound,
    double speed) : type_(type), outbound_(outbound), inbound_(inbound),
    speed_(speed) {}
        Bus* Generate(std::string name);
 private:
        std::string type_;
        Route* inbound_;
        Route* outbound_;
        double speed_;
};

#endif  // SRC_BUS_FACTORY_H_
