#ifndef CHARGING_STATION_H
#define CHARGING_STATION_H

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

/**
 * @class ChargingStation
 * @brief Represents a ChargingStation in a physical system
 *
 * ChargingStation can charge drones for now
 */
class ChargingStation : public IEntity {
 public:
  double positionX;
  double positionY;
  double positionZ;

  /**
   * @brief overriden function from Ientity.
   * This function won't do anything, a CS stays where it was created.
   * @param[in] dt The time of the simulation.
   */
  void update(double dt);

  /**
   * @brief Constructor
   * @param obj JSON object containing the ChargingStation's information
   */
  ChargingStation(JsonObject& obj);
};

#endif  // CHARGING_STATION_H
