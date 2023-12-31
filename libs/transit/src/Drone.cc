#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>
#include <typeinfo>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "Package.h"
#include "SimulationModel.h"
#include "SpinDecorator.h"

Drone::Drone(JsonObject& obj) : IEntity(obj) {
  available = true;
  battery = new BatteryDecorator(this);
}

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
}

void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination = new JumpDecorator(new AstarStrategy(
            packagePosition, finalDestination, model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
            new SpinDecorator(new JumpDecorator(new DfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
            new SpinDecorator(new SpinDecorator(new BfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
            new JumpDecorator(new SpinDecorator(new DijkstraStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else {
        toFinalDestination =
            new BeelineStrategy(packagePosition, finalDestination);
      }
    }
  }
}

void Drone::update(double dt) {
  publish();
  if (this->battery->getCharge() < 15) {
    goToCS(dt);
  }

  if (this->battery->getCharge() > 98 & this->battery->isCharging()) {
    delete toChargingStation;
    toChargingStation = nullptr;
    available = true;
    // this->battery->changeMode("idle");
  }
  this->battery->updateCharge(dt);  //////////////////////

  if (available) {
    if (model && model->scheduledDeliveries.size() > 0) {
      package = model->scheduledDeliveries.front();
    }
    if (package) {
      double total_dist =
          totalTripDistance(this->getPosition(), package->getPosition(),
                            package->getDestination());

      if (canCompleteTrip(total_dist)) {
        // std::cout << "                                                    "
        //              "                                can make it to item"
        //           << std::endl;
        getNextDelivery();
      } else {
        // std::cout << "                                                   "
        //              "                                            can not "
        //           << std::endl;
        goToCS(dt);
      }
    }
  }

  if (toPackage) {
    toPackage->move(this, dt);
    this->battery->changeMode("moving");  //////////////////////

    if (toPackage->isCompleted()) {
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);
    this->battery->changeMode("moving");  //////////////////////

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination->isCompleted()) {
      delete toFinalDestination;
      toFinalDestination = nullptr;
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;
      this->battery->changeMode("idle");
    }
  }
}

void Drone::goToCS(double dt) {
  // std::cout << "\n going to CS\n";
  Vector3 closestCS;
  double dist;
  std::tie(closestCS, dist) = getClosestChargingStation(position);

  if (!toChargingStation) {
    // std::cout << "\n made new startegy to move\n";
    closestCS[1] = closestCS[1] + 30;
    toChargingStation = new BeelineStrategy(position, closestCS);
  } else {
    available = false;
    toChargingStation->move(this, dt);
    this->battery->changeMode("moving");
    // std::cout << "\n moving to closest cs \n";

    if (toChargingStation->isCompleted()) {
      // std::cout << "                                                      "
      //              "                                  completed"
      //           << std::endl;
      this->battery->changeMode("charging");
      this->battery->changeState();
    }
  }
}

void Drone::setBattery(IEntity* battery) {
  this->battery = dynamic_cast<BatteryDecorator*>(battery);
}

bool Drone::canCompleteTrip(double dist) {
  double speed = this->getSpeed();
  double range = (dist / speed) * .6;

  if (this->battery->getCharge() - range > 15) {
    return true;
  }
  return false;
}

double Drone::totalTripDistance(Vector3 drone, Vector3 item, Vector3 customer) {
  double trip_total = 0;
  double dist;
  Vector3 closestCS;
  std::tie(closestCS, dist) =
      getClosestChargingStation(package->getDestination());

  // four points: Drone, item (package), customer (robot/destination), charging
  // station (CS)
  //
  //                      A             B                    C
  // three trips:   Drone -> item,  item->customer,  customer->CS
  //
  // so we calculate the distances of trips A and B using dist_A_to_B(A, B),
  // and we get the distance to the closest CS from the tuple returned from
  // the customers position getClosestChargingStation(customer)
  trip_total += dist_A_to_B(drone, item) + dist_A_to_B(item, customer) + dist;

  return trip_total;
}

// double dist = sqrt(pow((B[0] - A[0]), 2) + pow((B[1] - A[1]), 2) + pow((B[2]
// - A[2]), 2))
std::tuple<Vector3, double> Drone::getClosestChargingStation(
    Vector3 fromPosition) {
  std::vector<double> distances;
  std::vector<IEntity*> chargingStations =
      CSSingleton::getInstance()->getStations();

  for (int i = 0; i < chargingStations.size(); i++) {
    distances.push_back(
        dist_A_to_B(fromPosition, chargingStations.at(i)->getPosition()));
  }

  double shortestDist = distances.at(0);
  IEntity* thisCS = chargingStations.at(0);

  for (int i = 1; i < distances.size(); i++) {
    if (distances.at(i) < shortestDist) {
      shortestDist = distances.at(i);
      thisCS = chargingStations.at(i);
    }
  }
  return std::make_tuple(thisCS->getPosition(), shortestDist);
}

double Drone::dist_A_to_B(Vector3 vec_A, Vector3 vec_B) {
  return (sqrt(pow((vec_A[0] - vec_B[0]), 2) + pow((vec_A[1] - vec_B[1]), 2) +
               pow((vec_A[2] - vec_B[2]), 2)));
}

double Drone::getDroneCharge() const { return battery->getCharge(); }

void Drone::publish() {
  JsonObject droneDetails;
  droneDetails["droneName"] = this->getName();
  droneDetails["droneBatteryLevel"] =
      std::to_string(this->battery->getCharge());
  droneDetails["mode"] = this->battery->getMode();
  droneDetails["available"] = available;

  notifySubscribers(droneDetails);
}
