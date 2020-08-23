#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <ctime>
#include <string>
#include <gtest/gtest.h>
#include <fstream>
#include "../src/bus.h"
#include "../src/passenger.h"
#include "../src/random_passenger_generator.h"
#include "../src/route.h"
#include "../src/stop.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class StopTests : public ::testing::Test {
 protected:
    Stop * stop;
    Bus * bus;
    StopData stop_data;
    std::list<Passenger *> passengers_;

    std::ofstream test_in;
    std::ifstream correct_out, test_out;
    std::string output, expected_output;

    virtual void SetUp() {
        stop = new Stop (1,  44.973723, -93.235365);
        bus = new Bus("bus", NULL, NULL, 5, 1);
    }

    virtual void TearDown() {
        delete stop;
    }
};

TEST_F(StopTests, Constructor) {
    stop_data = stop->GetStopData();
    EXPECT_EQ(stop_data.id, "1");
	EXPECT_FLOAT_EQ(stop_data.position.x, 44.973723);
	EXPECT_FLOAT_EQ(stop_data.position.y, -93.235365);
	EXPECT_EQ(stop_data.num_people, 0);
}


TEST_F(StopTests, GetId) {
    EXPECT_EQ(stop->GetId(), 1);
    int id = stop->GetId();
    bool expected_out = (id == 2);
    EXPECT_EQ(expected_out, false);
}

TEST_F(StopTests, AddPassengersTest) {
    EXPECT_EQ(stop->AddPassengers(new Passenger(2,"p1")),1);
}

TEST_F(StopTests, LoadPassengers) {
    stop->AddPassengers(new Passenger(1,"p2"));
    EXPECT_EQ(stop->LoadPassengers(bus),1);
    stop->AddPassengers(new Passenger(2,"p2"));
    stop->AddPassengers(new Passenger(3,"p3"));
    EXPECT_EQ(stop->LoadPassengers(bus),2);
    stop->AddPassengers(new Passenger(4,"p4"));
    stop->AddPassengers(new Passenger(5,"p4"));
    stop->AddPassengers(new Passenger(6,"p4"));
    EXPECT_EQ(stop->LoadPassengers(bus),2);
    stop->AddPassengers(new Passenger(7,"p4"));
    EXPECT_EQ(stop->LoadPassengers(bus),0);
}

TEST_F(StopTests, Report_and_Update) {
    stop->AddPassengers(new Passenger(10,"p1"));
    stop->Update();
    stop->AddPassengers(new Passenger(13,"p3"));
    stop->Update();
    stop->AddPassengers(new Passenger(12,"p2"));
    test_in.open("../build/bin/stop_out.txt");
    if (!test_in.is_open()) {
        std::cout << "Unable to open file: stop_out.txt" << std::endl;
    }
    stop->Report(test_in);  // write output into file
    test_in.close();

    // correct_out.open("correct_stop_out.txt");
    // if (!correct_out.is_open()) {
    //     std::cout << "Unable to open file: correct_stop_out.txt" << std::endl;
    // }

    test_out.open("../build/bin/stop_out.txt");
    if (!test_out.is_open()) {
        std::cout << "Unable to open file: stop_out.txt" << std::endl;
    }

    // while (getline(test_out, output) &&
    //   getline(correct_out, expected_output)) {
    //     // std::cout << output << std::endl;
    //     // std::cout << expected_output << std::endl;
    //     EXPECT_EQ(expected_output, output);
    // }

    getline(test_out, output);
    EXPECT_EQ(output, "ID: 1");
    getline(test_out, output);
    EXPECT_EQ(output, "Passengers waiting: 3");
    getline(test_out, output);
    EXPECT_EQ(output, "Name: p1");
    getline(test_out, output);
    EXPECT_EQ(output, "Destination: 10");
    getline(test_out, output);
    EXPECT_EQ(output, "Total Wait: 2");
    getline(test_out, output);
    EXPECT_EQ(output, "	Wait at Stop: 2");
    getline(test_out, output);
    EXPECT_EQ(output, "	Time on bus: 0");

    getline(test_out, output);
    EXPECT_EQ(output, "Name: p3");
    getline(test_out, output);
    EXPECT_EQ(output, "Destination: 13");
    getline(test_out, output);
    EXPECT_EQ(output, "Total Wait: 1");
    getline(test_out, output);
    EXPECT_EQ(output, "	Wait at Stop: 1");
    getline(test_out, output);
    EXPECT_EQ(output, "	Time on bus: 0");

    getline(test_out, output);
    EXPECT_EQ(output, "Name: p2");
    getline(test_out, output);
    EXPECT_EQ(output, "Destination: 12");
    getline(test_out, output);
    EXPECT_EQ(output, "Total Wait: 0");
    getline(test_out, output);
    EXPECT_EQ(output, "	Wait at Stop: 0");
    getline(test_out, output);
    EXPECT_EQ(output, "	Time on bus: 0");
    test_out.close();
    // correct_out.close();
}

TEST_F(StopTests, GetStopData) {
    stop_data = stop->GetStopData();
    EXPECT_EQ(stop_data.id, "1");
	EXPECT_FLOAT_EQ(stop_data.position.x, 44.973723);
	EXPECT_FLOAT_EQ(stop_data.position.y, -93.235365);
	EXPECT_EQ(stop_data.num_people, 0);
}

TEST_F(StopTests, Update) {
    Passenger* passenger = new Passenger(10, "Zoe");
    stop->AddPassengers(passenger);
    stop->Update();
    EXPECT_EQ(passenger->GetTotalWait(), 1);
    stop->Update();
    Passenger* passenger2 = new Passenger(10, "Nick");
    stop->AddPassengers(passenger2);
    stop->Update();
    stop->Update();
    EXPECT_EQ(passenger->GetTotalWait(), 4);
    EXPECT_EQ(passenger2->GetTotalWait(), 2);
    passenger->GetOnBus();
    stop->Update();
    stop->Update();
    EXPECT_EQ(passenger->GetTotalWait(), 7);
}
