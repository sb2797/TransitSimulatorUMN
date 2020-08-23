/*
 * @Copyright 2019 3081 Staff, All rights reserved.
 * @file IObservable.h
 *
 * @author Srivatsan Balaji
 */

#include "src/bus.h"

Bus::Bus(std::string name, Route * out, Route * in,
          int capacity, double speed, std::string type) {
  name_ = name;
  outgoing_route_ = out;
  incoming_route_ = in;
  passenger_max_capacity_ = capacity;
  speed_ = speed;
  type_ = type;
  distance_remaining_ = 0;
  next_stop_ = out->GetDestinationStop();
  unloader_ = new PassengerUnloader;
  loader_ = new PassengerLoader;
}

bool Bus::IsTripComplete() {
  return outgoing_route_->IsAtEnd() && incoming_route_->IsAtEnd();
}

Route* Bus::CurrentRoute() {
  // Figure out if we're on the outgoing or incoming route
  if (!outgoing_route_->IsAtEnd()) {
    return outgoing_route_;
  }
  return incoming_route_;
}

void Bus::ToNextStop() {
  (CurrentRoute())->NextStop();
  if (!IsTripComplete()) {
    // NOTE: it's important we call CurrentRoute()
    // again, as NextStop() may have caused it to change.
    next_stop_ = (CurrentRoute())->GetDestinationStop();
    distance_remaining_ += (CurrentRoute())->GetNextStopDistance();  // now
    // we have to go to the next stop
    // note, if distance_remaining_ was negative because we had extra time
    // left over, that extra
    // time is effectively counted towards the next stop
  } else {
    next_stop_ = NULL;
    distance_remaining_ = 999;
  }
}

double Bus::UpdateDistance() {
  // Updates the distance remaining and returns the effective speed of the bus
  // Bus does not move if speed is negative or bus is at end of route
  if (IsTripComplete()) return 0;
  if (speed_ < 0) return 0;
  distance_remaining_ -= speed_;
  return speed_;
}

bool Bus::LoadPassenger(Passenger * new_passenger) {
  return loader_->LoadPassenger(new_passenger,
    passenger_max_capacity_, &passengers_);
}

int Bus::HandleBusStop() {
  // Return the number of passengers handled
  // write whether or not we moved in this step to local variable passed in

  // This function handles the stuff we have to do AT A MINIMUM when we
  // arrive at a bus stop

  int passengers_handled = 0;
  passengers_handled += UnloadPassengers();
  passengers_handled += next_stop_->LoadPassengers(this);

  // if any passengers on or off, all distance to next stop is left
  // but, if we didn't handle any passengers here, any negative will
  // affect the distance remaining (see addition below)

  if (passengers_handled != 0) {
      distance_remaining_ = 0;
  }
  return passengers_handled;
}
bool Bus::Move() {
  // update all passengers FIRST
  // new passengers will get "updated" when getting on the bus
  for(auto* passenger : passengers_) {
    passenger->Update();
  }
  double speed = UpdateDistance();  // actually move
  if(!IsTripComplete() && distance_remaining_ <= 0) {
    int passengers_handled = HandleBusStop();  // load & unload
    if (passengers_handled >= 0) {
      distance_remaining_ = 0;
      // if we spent time (un)loading, we don't get to count excess
      // speed towards next stop
    }
    ToNextStop();  // switch to next stop
  }
  return (speed > 0);
}

void Bus::Update() {  // using common Update format
  Move();
  UpdateBusData();
  NotifyObservers(&bus_data_);
// If distance_remaining <= 0 then the bus should decide whether it needs
// to stop.
// It should stop regradless of the speed because there are passengers
// load or unloaded.
// It should continue to move if because there are no passengers load
// or unloaded unless distance_remaining = 0
}

void Bus::Report(std::ostream& out) {
  out << "Name: " << name_ << std::endl;
  out << "Speed: " << speed_ << std::endl;
  out << "Bus Type: " << type_ << std::endl;
  out << "Distance to next stop: " << distance_remaining_ << std::endl;
  out << "\tPassengers (" << passengers_.size() << "): " << std::endl;
  for (std::list<Passenger *>::iterator it = passengers_.begin();
                                        it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}

int Bus::UnloadPassengers() {
  return unloader_->UnloadPassengers(passengers_, next_stop_);
}

void Bus::UpdateBusData() {
  /* Store a unique identifier for the bus(name) in the BusData id atttribute.
  Use the current route to get the previous stop (on the current route).
  You will need to figure out a way (write a new function, etc.) to get the
  bus's previous stop. Compute and store the average of the latitudes and
  longitudes belonging to the current and previous stops.
  Store the averages in the BusData position attribute. (This algorithm is
  somewhat clunky and not realistic. We may update this in the future.)
  Populate the numPassengers and capacity attributes within your BusData
  variable.*/
  bus_data_.id = name_;
  // Get the correct route and early exit
  Route * current_route = outgoing_route_;
  if (outgoing_route_->IsAtEnd()) {
    if (incoming_route_->IsAtEnd()) { return; }
    current_route = incoming_route_;
  }
  Stop * prevStop = current_route->PrevStop();
  Stop * nextStop = current_route->GetDestinationStop();
  double distanceBetween = current_route->GetNextStopDistance();
  double ratio;
  // Need to check if we are at the first stop
  if (distanceBetween - 0.00001 < 0) {
    ratio = 1;
  } else {
    ratio = distance_remaining_ / distanceBetween;
    if (ratio < 0) {
      ratio = 0;
      distance_remaining_ = 0;
    }
  }
  // This ratio shows us how far from the previous stop are we in a ratio
  // from 0 to 1
  Position p;
  p.x = (nextStop->GetLongitude() * (1 - ratio) +
  prevStop->GetLongitude() * ratio);
  p.y = (nextStop->GetLatitude() * (1 - ratio) +
  prevStop->GetLatitude() * ratio);
  bus_data_.position = p;
  bus_data_.num_passengers = static_cast<int>(passengers_.size());
  bus_data_.capacity = passenger_max_capacity_;
}
BusData Bus::GetBusData() const {
    return bus_data_;
}
