#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "IEntity.h"
#include <iomanip>


/**
 * @brief this class inhertis from the IStrategy class and is represents
 * a celebration decorator where the entity will celebrate according to it.
 */

class Drone;

class BatteryDecorator : public IEntity {
 public:
  /**
   * @brief Construct a new Jump Decorator object
   *
   * @param[in] strategy the strategy to decorate onto
   * @param[in] time how long to celebrate
   * @param[in] jumpHeight how far up to jump
   */
  BatteryDecorator(IEntity* drone);
  BatteryDecorator(IEntity* drone, double charge);

  /**
   * @brief Make the entity celebrate with the jump behavior.
   * 
   * @param entity Entity to celebrate
   * @param dt Delta Time
   */
  void update(double dt);
  void updateCharge(double dt, double dist = 0);

  double getCharge();

  bool isCharging();

  void changeState();

  void changeMode(std::string newMode);

  std::string getMode();


 private:
  double dist = 0;
  double charge;
  bool charging = false;
  Drone* drone;
  int counter = 0;
  std::string mode = "idle";  // moving,  movingWeight,  charging
};

#endif  // BATTERY_DECORATOR_H_
