#include "ChargingStationFactory.h"
#include "CSSingleton.h"


IEntity* ChargingStationFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("ChargingStation") == 0) {
    ChargingStation* station = new ChargingStation(entity);
    CSSingleton::getInstance()->addStation(station);
    std::cout << "ChargingStation Created" << std::endl;
    return station;
  }
  return nullptr;
}
