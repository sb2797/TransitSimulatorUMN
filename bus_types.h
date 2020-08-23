/**
 * @file Bus.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_BUS_TYPES_H_
#define SRC_BUS_TYPES_H_

#include "./bus.h"

class SmallBus : public Bus {
 public:
      SmallBus(std::string name, Route* out, Route* in, double speed):
            Bus(name, out, in, 30, speed, "Small") { }
};

class MediumBus : public Bus {
 public:
        MediumBus(std::string name, Route* out, Route* in, double speed):
            Bus(name, out, in, 60, speed, "Medium") { }
};

class LargeBus : public Bus {
 public:
        LargeBus(std::string name, Route* out, Route* in, double speed):
            Bus(name, out, in, 90, speed, "Large") { }
};

#endif  //SRC_BUS_TYPES_H_
