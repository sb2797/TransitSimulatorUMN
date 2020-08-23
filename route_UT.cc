#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <ctime>
#include <string>
#include <gtest/gtest.h>
#include <fstream>

#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/route.h"
#include "../src/bus.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/


class RouteTests  : public ::testing::Test {
 protected:
    Route * CC_EB;
    Route * CC_WB;

    Stop * current_stop;
    Stop * next_stop;
    Stop * destination;

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

      //   CC_EB_generator->GeneratePassengers();
      //   CC_WB_generator->GeneratePassengers();
  /*  OverridePassengerGenerator * CC_EB_generator
              = new OverridePassengerGenerator(CC_EB_probs, CC_EB_stops_list);
    OverridePassengerGenerator * CC_WB_generator
              = new OverridePassengerGenerator(CC_WB_probs, CC_WB_stops_list);


       CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops,
                            CC_EB_distances, 4, CC_EB_generator);
       CC_WB = new Route("Campus Connector - Westbound", CC_WB_stops,
                            CC_WB_distances, 4, CC_WB_generator);
*/
    }

    virtual void TearDown() {
        delete CC_EB;
        delete CC_WB;
    }
};

TEST_F(RouteTests, Constructor) {
	CC_EB->UpdateRouteData();
  	CC_WB->UpdateRouteData();
	RouteData route_data1 = CC_EB->GetRouteData();
	RouteData route_data2 = CC_WB->GetRouteData();
	EXPECT_EQ(route_data1.id, "Campus Connector - Eastbound");
	EXPECT_EQ(route_data2.id, "Campus Connector - Westbound");
	EXPECT_EQ((CC_EB->GetStops()).size(), 4);
	EXPECT_EQ((CC_WB->GetStops()).size(), 4);
}

TEST_F(RouteTests, Clone) {
	Route* clone_route = CC_WB->Clone();
	std::list<Stop *> stops = clone_route->GetStops();
	std::list<Stop *>::iterator it = stops.begin();
	EXPECT_EQ((*it)->GetId(), 4);
	advance(it, 1);
	EXPECT_EQ((*it)->GetId(), 5);
	advance(it, 1);
	EXPECT_EQ((*it)->GetId(), 6);
}


TEST_F(RouteTests, IsAtEnd) {
    EXPECT_EQ(CC_WB->IsAtEnd(),false);
    EXPECT_EQ(CC_EB->IsAtEnd(),false);
    for (int i = 0; i < 4; i++) {
        CC_WB->NextStop();
        CC_EB->NextStop();
    }
    EXPECT_EQ(CC_WB->IsAtEnd(),true);
    EXPECT_EQ(CC_EB->IsAtEnd(),true);

}

TEST_F(RouteTests, GetDestinationStop) {
    destination = CC_EB->GetDestinationStop();
    EXPECT_EQ(destination->GetId(), 0);

    destination = CC_WB->GetDestinationStop();
    EXPECT_EQ(destination->GetId(), 4);

}

TEST_F(RouteTests,NextStop) {
    current_stop = CC_EB->GetDestinationStop();
    EXPECT_EQ(current_stop->GetId(), 0);

    CC_EB->NextStop();
    next_stop = CC_EB->GetDestinationStop();
    EXPECT_EQ(next_stop->GetId(), 1);

    current_stop = CC_WB->GetDestinationStop();
    EXPECT_EQ(current_stop->GetId(), 4);

    CC_WB->NextStop();
    next_stop = CC_WB->GetDestinationStop();
    EXPECT_EQ(next_stop->GetId(), 5);
}


TEST_F(RouteTests, GetTotalRouteDistance) {
    EXPECT_EQ(CC_WB->GetTotalRouteDistance(), 6.0);
    EXPECT_EQ(CC_EB->GetTotalRouteDistance(), 6.0);
}

TEST_F(RouteTests, GetNextStopDistanceTest) {
    CC_WB->NextStop();
    EXPECT_EQ(CC_WB->GetNextStopDistance(), 2.0);
    CC_EB->NextStop();
    EXPECT_EQ(CC_EB->GetNextStopDistance(), 2.0);
}

TEST_F(RouteTests, GetPreviousStop) {
    current_stop = CC_WB->GetDestinationStop();
    CC_WB->NextStop();
    EXPECT_EQ(CC_WB->PrevStop(), current_stop);
    current_stop = CC_EB->GetDestinationStop();
    CC_EB->NextStop();
    EXPECT_EQ(CC_EB->PrevStop(), current_stop);
}

TEST_F(RouteTests, Update) {
	Passenger* passenger = new Passenger(10, "Zoe");
    Passenger* passenger2 = new Passenger(10, "Nick");
	std::list<Stop *> stops = CC_EB->GetStops();
	std::list<Stop *>::iterator it = stops.begin();
	std::advance(it, 1);
	(*it)->AddPassengers(passenger);
	std::advance(it, 1);
	(*it)->AddPassengers(passenger2);
	CC_EB->Update();
	EXPECT_EQ(passenger->GetTotalWait(), 1);
	EXPECT_EQ(passenger2->GetTotalWait(), 1);
	CC_EB->Update();
	CC_EB->Update();
	CC_EB->Update();
	EXPECT_EQ(passenger->GetTotalWait(), 4);
	EXPECT_EQ(passenger2->GetTotalWait(), 4);
}

TEST_F(RouteTests, GetName) {
	EXPECT_EQ(CC_EB->GetName(), "Campus Connector - Eastbound");
	EXPECT_EQ(CC_WB->GetName(), "Campus Connector - Westbound");
}

TEST_F(RouteTests, GetStops) {
	std::list<Stop *> stops = CC_EB->GetStops();
	std::list<Stop *>::iterator it = stops.begin();
	EXPECT_EQ((*it)->GetId(), 0);
	std::advance(it, 1);
	EXPECT_EQ((*it)->GetId(), 1);
	std::advance(it, 2);
	EXPECT_EQ((*it)->GetId(), 3);
}

TEST_F(RouteTests, UpdateRouteData) {
	CC_WB->UpdateRouteData();
	RouteData route_data = CC_WB->GetRouteData();
	EXPECT_EQ(route_data.id, "Campus Connector - Westbound");
	EXPECT_EQ((CC_WB->GetStops()).size(), 4);
}

TEST_F(RouteTests, GetRouteData) {
	CC_EB->UpdateRouteData();
	RouteData route_data = CC_EB->GetRouteData();
	EXPECT_EQ(route_data.id, "Campus Connector - Eastbound");
	EXPECT_EQ((CC_EB->GetStops()).size(), 4);
}
