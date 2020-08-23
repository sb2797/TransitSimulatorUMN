#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
#include "../src/bus.h"
#include "../src/passenger.h"
#include "../src/route.h"
#include "../src/stop.h"
/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class BusTests : public ::testing::Test {
 protected:
    Bus* bus;
    Stop * stop;
    Passenger* pass = new Passenger(2, "triple you");
    Passenger* pass2 = new Passenger(3, "middle autumn festival");
    Passenger* pass3 = new Passenger(3, "shin");

    std::ofstream test_in;
    std::ifstream correct_out, test_out;
    std::string output, expected_output;

    virtual void SetUp() {
        Stop ** CC_EB_stops = new Stop *[4];
        Stop ** CC_WB_stops = new Stop *[4];
        std::list<Stop *> CC_EB_stops_list;
        std::list<Stop *> CC_WB_stops_list;

        Stop * stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
        //   student union station
        Stop * stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
        //   Oak St & Washington Ave
        Stop * stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);
        //   before transit
        Stop * stop_CC_EB_4 = new Stop(3, 44.975837, -93.222174);

        Stop * stop_CC_WB_1 = new Stop(4, 44.984630, -93.186352);
    //   Buford & Gartner
        Stop * stop_CC_WB_2 = new Stop(5, 44.984482, -93.181657);
        //   Fairgrounds
        Stop * stop_CC_WB_3 = new Stop(6, 44.983703, -93.178846);
        //   Tway
        Stop * stop_CC_WB_4 = new Stop(7, 44.980663, -93.180808);

        CC_EB_stops_list.push_back(stop_CC_EB_1);
        CC_EB_stops[0] = stop_CC_EB_1;
        CC_EB_stops_list.push_back(stop_CC_EB_2);
        CC_EB_stops[1] = stop_CC_EB_2;
        CC_EB_stops_list.push_back(stop_CC_EB_3);
        CC_EB_stops[2] = stop_CC_EB_3;
        CC_EB_stops_list.push_back(stop_CC_EB_4);
        CC_EB_stops[3] = stop_CC_EB_4;

        CC_WB_stops_list.push_back(stop_CC_WB_1);
        CC_WB_stops[0] = stop_CC_WB_1;
        CC_WB_stops_list.push_back(stop_CC_WB_2);
        CC_WB_stops[1] = stop_CC_WB_2;
        CC_WB_stops_list.push_back(stop_CC_WB_3);
        CC_WB_stops[2] = stop_CC_WB_3;
        CC_WB_stops_list.push_back(stop_CC_WB_4);
        CC_WB_stops[3] = stop_CC_WB_4;

        double * CC_EB_distances = new double[4];
        double * CC_WB_distances = new double[4];
        CC_EB_distances[0] = 2;
        CC_EB_distances[1] = 2;
        CC_EB_distances[2] = 2;

        CC_WB_distances[0] = 2;
        CC_WB_distances[1] = 2;
        CC_WB_distances[2] = 2;

        std::list<double> CC_EB_probs;  // realistic .15, .3, .025, .05, .05, 0
        CC_EB_probs.push_back(.15);   // WB
        CC_EB_probs.push_back(.3);    // CMU
        CC_EB_probs.push_back(.025);  // O&W
        CC_EB_probs.push_back(.05);   // Pre-transit

        std::list<double> CC_WB_probs;  // realistic .35, .05, .01, .01, .2, 0
        CC_WB_probs.push_back(.35);     // SPSC
        CC_WB_probs.push_back(.05);     // Buford
        CC_WB_probs.push_back(.01);     // State fair
        CC_WB_probs.push_back(.01);

/*
        OverridePassengerGenerator * CC_EB_generator
            = new OverridePassengerGenerator(CC_EB_probs, CC_EB_stops_list);
        OverridePassengerGenerator * CC_WB_generator
            = new OverridePassengerGenerator(CC_WB_probs, CC_WB_stops_list);
*/

        //CC_EB_generator->GeneratePassengers();
        //CC_WB_generator->GeneratePassengers();

      //  Route * CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops,
        //                    CC_EB_distances, 4, CC_EB_generator);
        //Route * CC_WB = new Route("Campus Connector - Westbound", CC_WB_stops,
          //                  CC_WB_distances, 4, CC_WB_generator);

    //    bus = new Bus ("bus", CC_EB, CC_WB, 5, 1);

    }

        virtual void TearDown() {
        delete bus;
    }
};


TEST_F(BusTests, Constructor) {
	bus->UpdateBusData();
	BusData bus_data = bus->GetBusData();
	EXPECT_EQ(bus_data.id, "bus");
	EXPECT_FLOAT_EQ(bus_data.position.x, 44.972392);
	EXPECT_FLOAT_EQ(bus_data.position.y, -93.243774);
	EXPECT_EQ(bus_data.num_passengers, 0);
	EXPECT_EQ(bus_data.capacity, 5);
}

TEST_F(BusTests, LoadPassenger) {
    bus->LoadPassenger(pass);
    EXPECT_EQ(bus->GetNumPassengers(), 1);
    bus->LoadPassenger(pass2);
    EXPECT_EQ(bus->GetNumPassengers(), 2);
    EXPECT_EQ(bus->LoadPassenger(pass3), true);
    EXPECT_EQ(bus->GetNumPassengers(), 3);
    bus->LoadPassenger(pass);
    bus->LoadPassenger(pass2);
    bus->LoadPassenger(pass2);
    EXPECT_EQ(bus->GetNumPassengers(), 5);
    EXPECT_EQ(bus->LoadPassenger(pass3),false);
    EXPECT_EQ(bus->GetNumPassengers(), 5);

}

TEST_F(BusTests, UnloadPassenger) {
    bus->LoadPassenger(pass);
    bus->LoadPassenger(pass2);
    bus->LoadPassenger(pass3);
  //  EXPECT_EQ(bus->UnloadPassengers((1), 0);
    //EXPECT_EQ(bus->UnloadPassengers((3), 2);
    EXPECT_EQ(bus->GetNumPassengers(), 1);
  //  bus->UnloadPassengers(2);
    EXPECT_EQ(bus->GetNumPassengers(), 0);
}

TEST_F(BusTests, IsTripComplete) {
    EXPECT_EQ(bus->IsTripComplete(), false);
    for (int i = 0; i < 5; i++) {
        bus->Update();
    }
    EXPECT_EQ(bus->IsTripComplete(), false);
    for (int i = 0; i < 7; i++) {
        bus->Update();
    }
    EXPECT_EQ(bus->IsTripComplete(), true);
}


TEST_F(BusTests, GetBusData) {
	bus->UpdateBusData();
	BusData bus_data = bus->GetBusData();
	EXPECT_EQ(bus_data.id, "bus");
	EXPECT_FLOAT_EQ(bus_data.position.x, 44.972392);
	EXPECT_FLOAT_EQ(bus_data.position.y, -93.243774);
	EXPECT_EQ(bus_data.num_passengers, 0);
	EXPECT_EQ(bus_data.capacity, 5);
}

TEST_F(BusTests, GetName) {
	EXPECT_EQ(bus->GetName(), "bus");
}

TEST_F(BusTests, GetCapacity) {
	EXPECT_EQ(bus->GetCapacity(), 5);
}

TEST_F(BusTests, GetNumPassengers) {
    bus->LoadPassenger(pass);
    bus->LoadPassenger(pass2);
    bus->LoadPassenger(pass3);
    EXPECT_EQ(bus->GetNumPassengers(), 3);
}

TEST_F(BusTests, UpdateBusData) {
	bus->UpdateBusData();
	BusData bus_data = bus->GetBusData();
	EXPECT_EQ(bus_data.id, "bus");
	EXPECT_FLOAT_EQ(bus_data.position.x, 44.972392);
	EXPECT_FLOAT_EQ(bus_data.position.y, -93.243774);
	EXPECT_EQ(bus_data.num_passengers, 0);
	EXPECT_EQ(bus_data.capacity, 5);
}

TEST_F(BusTests, Move) {
    EXPECT_EQ(bus->Move(), true);
}

TEST_F(BusTests, Update) {

    test_in.open("../build/bin/bus_out.txt");
    if (!test_in.is_open()) {
        std::cout << "Unable to open file: bus_out.txt" << std::endl;
    }
    bus->Report(test_in);  // write output into file
    bus->Update();
    bus->LoadPassenger(pass);
    bus->LoadPassenger(pass2);
    bus->LoadPassenger(pass3);
    bus->Report(test_in);
    bus->Update();
    bus->Report(test_in);
    for (int i = 0; i < 12; i++) {
        bus->Update();
    }

    bus->Report(test_in);
    test_in.close();


    // correct_out.open("correct_bus_out.txt");
    // if (!correct_out.is_open()) {
    //     std::cout << "Unable to open file: correct_bus_out.txt" << std::endl;
    // }

    test_out.open("../build/bin/bus_out.txt");
    if (!test_out.is_open()) {
        std::cout << "Unable to open file: bus_out.txt" << std::endl;
    }

    // while(!test_out.eof() && !correct_out.eof()){
    //     test_out >> output;
    //     correct_out >> expected_output;
    //     EXPECT_EQ(output, expected_output);
    // }

    // while (getline(test_out, output) &&
    //   getline(correct_out, expected_output)) {
    //     // std::cout << output << std::endl;
    //     // std::cout << expected_output << std::endl;
    //     EXPECT_EQ(output, expected_output);
    // }

    getline(test_out, output);
    EXPECT_EQ(output, "Name: bus");
    getline(test_out, output);
    EXPECT_EQ(output, "Speed: 1");
    getline(test_out, output);
    EXPECT_EQ(output, "Distance to next stop: 0");
    getline(test_out, output);
    EXPECT_EQ(output, "	Passengers (0): ");

    getline(test_out, output);
    EXPECT_EQ(output, "Name: bus");
    getline(test_out, output);
    EXPECT_EQ(output, "Speed: 1");
    getline(test_out, output);
    EXPECT_EQ(output, "Distance to next stop: 1");
    getline(test_out, output);
    EXPECT_EQ(output, "	Passengers (3): ");

    getline(test_out, output);
    EXPECT_EQ(output, "Name: triple you");
    getline(test_out, output);
    EXPECT_EQ(output, "Destination: 2");
    getline(test_out, output);
    EXPECT_EQ(output, "Total Wait: 1");
    getline(test_out, output);
    EXPECT_EQ(output, "	Wait at Stop: 0");
    getline(test_out, output);
    EXPECT_EQ(output, "	Time on bus: 1");

    getline(test_out, output);
    EXPECT_EQ(output, "Name: middle autumn festival");
    getline(test_out, output);
    EXPECT_EQ(output, "Destination: 3");
    getline(test_out, output);
    EXPECT_EQ(output, "Total Wait: 1");
    getline(test_out, output);
    EXPECT_EQ(output, "	Wait at Stop: 0");
    getline(test_out, output);
    EXPECT_EQ(output, "	Time on bus: 1");

    getline(test_out, output);
    EXPECT_EQ(output, "Name: shin");
    getline(test_out, output);
    EXPECT_EQ(output, "Destination: 3");
    getline(test_out, output);
    EXPECT_EQ(output, "Total Wait: 1");
    getline(test_out, output);
    EXPECT_EQ(output, "	Wait at Stop: 0");
    getline(test_out, output);
    EXPECT_EQ(output, "	Time on bus: 1");

    getline(test_out, output);
    EXPECT_EQ(output, "Name: bus");
    getline(test_out, output);
    EXPECT_EQ(output, "Speed: 1");
    getline(test_out, output);
    EXPECT_EQ(output, "Distance to next stop: 0");
    getline(test_out, output);
    EXPECT_EQ(output, "	Passengers (3): ");

    getline(test_out, output);
    EXPECT_EQ(output, "Name: triple you");
    getline(test_out, output);
    EXPECT_EQ(output, "Destination: 2");
    getline(test_out, output);
    EXPECT_EQ(output, "Total Wait: 2");
    getline(test_out, output);
    EXPECT_EQ(output, "	Wait at Stop: 0");
    getline(test_out, output);
    EXPECT_EQ(output, "	Time on bus: 2");

    getline(test_out, output);
    EXPECT_EQ(output, "Name: middle autumn festival");
    getline(test_out, output);
    EXPECT_EQ(output, "Destination: 3");
    getline(test_out, output);
    EXPECT_EQ(output, "Total Wait: 2");
    getline(test_out, output);
    EXPECT_EQ(output, "	Wait at Stop: 0");
    getline(test_out, output);
    EXPECT_EQ(output, "	Time on bus: 2");

    getline(test_out, output);
    EXPECT_EQ(output, "Name: shin");
    getline(test_out, output);
    EXPECT_EQ(output, "Destination: 3");
    getline(test_out, output);
    EXPECT_EQ(output, "Total Wait: 2");
    getline(test_out, output);
    EXPECT_EQ(output, "	Wait at Stop: 0");
    getline(test_out, output);
    EXPECT_EQ(output, "	Time on bus: 2");

    getline(test_out, output);
    EXPECT_EQ(output, "Name: bus");
    getline(test_out, output);
    EXPECT_EQ(output, "Speed: 1");
    getline(test_out, output);
    EXPECT_EQ(output, "Distance to next stop: 1");
    getline(test_out, output);
    EXPECT_EQ(output, "	Passengers (2): ");

    getline(test_out, output);
    EXPECT_EQ(output, "Name: middle autumn festival");
    getline(test_out, output);
    EXPECT_EQ(output, "Destination: 3");
    getline(test_out, output);
    EXPECT_EQ(output, "Total Wait: 14");
    getline(test_out, output);
    EXPECT_EQ(output, "	Wait at Stop: 0");
    getline(test_out, output);
    EXPECT_EQ(output, "	Time on bus: 14");

    getline(test_out, output);
    EXPECT_EQ(output, "Name: shin");
    getline(test_out, output);
    EXPECT_EQ(output, "Destination: 3");
    getline(test_out, output);
    EXPECT_EQ(output, "Total Wait: 14");
    getline(test_out, output);
    EXPECT_EQ(output, "	Wait at Stop: 0");
    getline(test_out, output);
    EXPECT_EQ(output, "	Time on bus: 14");





    test_out.close();
    // correct_out.close();
}
