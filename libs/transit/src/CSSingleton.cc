#include "CSSingleton.h"

CSSingleton* CSSingleton::instance = nullptr;

CSSingleton::CSSingleton() {}

CSSingleton* CSSingleton::getInstance() {
  if (instance == nullptr) {
    instance = new CSSingleton();
  }
  return instance;
}

void CSSingleton::addStation(IEntity* station) {
  chargingStations.push_back(station);
}

std::vector<IEntity*> CSSingleton::getStations() { return chargingStations; }
