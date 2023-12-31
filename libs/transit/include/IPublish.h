#ifndef PUBLISH_H_
#define PUBLISH_H_

#include <vector>

#include "ISubscribe.h"
#include "util/json.h"

/**
 * @class IPublish
 * @brief This interface defines the behavior of a publisher object that can
 * notify its subscribers.
 *
 * The IPublish interface provides a way for objects to broadcast messages to
 * other interested objects. It allows for loose coupling and decoupling of
 * objects, making them more modular and easier to maintain.
 */
class IPublish {
 public:
  /**
   * @brief Subscribes an object to receive notifications from this publisher.
   * Gets added to a list of subscribers.
   * @param[in] s The object to subscribe.
   */
  void subscribe(ISubscribe* s);

  /**
   * @brief Unsubscribes an object from receiving notifications from this
   * publisher.
   * @param[in] s The object to unsubscribe.
   */
  void unsubscribe(ISubscribe* s);

  /**
   * @brief Notifies all subscribed objects about an event by sending a JSON
   * object.
   * @param[in] obj The JSON object containing the information about the event.
   */
  void notifySubscribers(const JsonObject& obj);

 private:
  std::vector<ISubscribe*> subscribers;
};

#endif
