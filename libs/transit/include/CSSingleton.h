#ifndef CSSINGLETON_H
#define CSSINGLETON_H

#include <vector>

#include "ChargingStation.h"
#include "ChargingStationFactory.h"
#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

/**
 * @class CSSingleton
 * @brief A singleton that stores all of the charging stations (CS) instances.
 *
 * This can be used by any other object to access the location of all the CS.
 */
class CSSingleton {
 public:
  /**
   * @brief Retrieves the singleton instance of the CSSingleton class.
   *
   * This method provides access to the single instance of the CSSingleton
   * class. If the instance does not exist, it is created. This ensures that
   * there is only one instance of the CSSingleton class throughout the program,
   * providing a global point of access to it.
   *
   * @return CSSingleton* A pointer to the singleton instance of the CSSingleton
   * class.
   */
  static CSSingleton* getInstance();

  /**
   * @brief Adds a CS to the vector of CS
   * @param[in] station The current CS to add to the vector.
   */
  void addStation(IEntity* station);

  /**
   * @brief Adds a CS to the vector of CS
   * @return Return a vector of IEntity CS.
   */
  std::vector<IEntity*> getStations();

 private:
  CSSingleton();
  static CSSingleton* instance;
  std::vector<IEntity*> chargingStations;
};
#endif
