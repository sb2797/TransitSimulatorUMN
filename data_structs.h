/*
* Copyright 3081. All rights reserved
* @author Srivatsan Balaji
*/

#ifndef SRC_DATA_STRUCTS_H_
#define SRC_DATA_STRUCTS_H_

#include <string>
#include <vector>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class defintion that holds several structs for holding data
 *
 * These structs hold much of the information for their respective class
 * bus, stops, and routes so that this data can be accessed easily by the
 * vis_sim.
 */

struct Position{
    Position() : x(0), y(0) {}
    float x;
    float y;
};

struct BusData {
    BusData() : id(""), position(Position()), num_passengers(0), capacity(0) {}
    std::string id;
    Position position;
    int num_passengers;
    int capacity;
};

struct StopData {
    StopData() : id(""), position(Position()), num_people(0) {}
    std::string id;
    Position position;
    int num_people;
};

struct RouteData {
    RouteData() : id(""), stops(std::vector<StopData>(0)) {}
    std::string id;
    std::vector<StopData> stops;
};

#endif  // SRC_DATA_STRUCTS_H_
