#include "BatteryDecorator.h"

#include "SimulationModel.h"

BatteryDecorator::BatteryDecorator(IEntity* drone) {
  this->drone = dynamic_cast<Drone*>(drone);
  this->charge = 100.0;

  this->drone->setBattery(this);
}

BatteryDecorator::BatteryDecorator(IEntity* drone, double charge) {
  this->drone = dynamic_cast<Drone*>(drone);
  this->charge = charge;
}

void BatteryDecorator::update(double dt) {  // doesn't work
                                            // this->drone->update(dt);
                                            // updateCharge(dt);
  // std::cout << "This is    : " << this->getCharge() << std::endl;
}

void BatteryDecorator::updateCharge(double dt, double dist) {
  // mode: idle,  moving,  movingWeight,  charging
  //   std::cout << "This is the charge: " << std::setprecision(2) <<
  //   getCharge()  <<  "   mode: " << mode <<  "   "<< isCharging()<<
  //   std::endl;
  if (charging) {
    charge = charge + (1 * dt);
    if (charge > 100) {
      changeState();
      changeMode("idle");
      charge = 100.0;
    }
  } else {
    if (mode == "idle") {
      charge = charge - (.1 * dt);
    }
    if (mode == "moving") {
      charge = charge - (.6 * dt);
    }
  }
}

double BatteryDecorator::getCharge() { return charge; }

bool BatteryDecorator::isCharging() { return charging; }

void BatteryDecorator::changeState() {
  if (isCharging()) {
    charging = false;  // not charging   0
  } else {
    charging = true;  //    charging   1
  }
}

void BatteryDecorator::changeMode(std::string newMode) { mode = newMode; }

std::string BatteryDecorator::getMode() { return mode; }

// // when dorne is at the charging station position, update that it
// // is charging. Then the update function should start incrementing
// // the battery charge.
