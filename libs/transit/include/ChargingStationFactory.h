#ifndef CHARGING_STATION_FACTORY_H_
#define CHARGING_STATION_FACTORY_H_

#include <vector>

#include "ChargingStation.h"
#include "IEntityFactory.h"

/**
 * @class ChargingStationFactory
 *@brief Charging Station Factory to produce Charging Station class.
 **/
class ChargingStationFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for ChargingStationFactory class.
   **/
  virtual ~ChargingStationFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   * nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
