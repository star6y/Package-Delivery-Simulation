#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "BatteryDecorator.h"
#include "CSSingleton.h"
#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

class Package;

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();

  /**
   * @brief Gets the next delivery in the scheduler
   */
  void getNextDelivery();

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   */
  void update(double dt);

  /**
   * @brief Removing the copy constructor operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;

  /**
   * @brief Removing the assignment operator
   * so that drones cannot be copied.
   */
  Drone& operator=(const Drone& drone) = delete;

  /**
   * @brief Directs the drone to move towards the nearest charging station.
   * The drone's path and behavior during this process are determined by the
   * BeelineStrategy.
   * @param dt Delta time, representing the time step for the simulation update.
   */
  void goToCS(double dt);

  /**
   * @brief Sets the battery component of the drone.
   * This function is used to initialize or change the battery being used by the
   * drone. Allows the drone to access battery functions and variables, such as
   * the battery's charge.
   * @param battery Pointer to an IEntity that represents the new battery
   * component.
   */
  void setBattery(IEntity* battery);

  /**
   * @brief Determines if the drone has sufficient battery charge to complete a
   * given trip. This function is essential for planning the drone's route,
   * ensuring it has enough charge for its journey.
   * @param dist The estimated distance of the planned trip in simulation units.
   * @return True if the drone can complete the trip with its current battery
   * level, false otherwise.
   */
  bool canCompleteTrip(double dist);

  /**
   * @brief Calculates the total distance of a delivery trip.
   * Uses the 3 points to calculate the distance, and adds a 4th point to ensure
   * the drone can make it to a charging station at the end.
   * @param drone The current position of the drone.
   * @param item The position of the item/package to be picked up.
   * @param customer The destination position where the item/package needs to be
   * delivered.
   * @return The total estimated distance of the entire trip in units.
   */
  double totalTripDistance(Vector3 drone, Vector3 item, Vector3 customer);

  /**
   * @brief Identifies the closest charging station from a given position and
   * calculates the distance to it. This function finds the nearest charging
   * point when the battery is low.
   * @param fromPosition The current position from which the nearest charging
   * station is to be identified.
   * @return A tuple containing the position of the closest charging station and
   * the distance to this station in units.
   */
  std::tuple<Vector3, double> getClosestChargingStation(Vector3 fromPosition);

  /**
   * @brief Calculates the Euclidean distance between two points in 3D space.
   *  This is used for distance measurement in various drone operations.
   * @param vec_A The first point in 3D space.
   * @param vec_B The second point in 3D space.
   * @return The Euclidean distance between vec_A and vec_B in units.
   */
  double dist_A_to_B(Vector3 vec_A, Vector3 vec_B);

  /**
   * @brief Retrieves the current charge level of the drone's battery.
   *  This function is important for monitoring the drone's battery status
   *  and making decisions based on it.
   * @return The current charge level of the drone's battery as a percentage.
   */
  double getDroneCharge() const;

  /**
   * @brief Publishes the current state of the drone, including details
   *  such as name, battery level, and availability. This information is
   *  used for monitoring and displaying the drone's status in the system.
   */
  void publish();

 private:
  bool available = false;
  bool pickedUp = false;

  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  IStrategy* toFinalDestination = nullptr;

  IStrategy* toChargingStation = nullptr;
  BatteryDecorator* battery = nullptr;
};

#endif
