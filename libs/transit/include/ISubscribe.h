#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H

#include "util/json.h"

/**
 * @class ISubscribe
 * @brief Represents the subscribers, who will receive updates on events.
 *
 * In the simualtion, those subscirbed will push the events forward, in
 * our case to the front end. The updates sent by the publisher will show
 * up on the front end.
 */
class ISubscribe {
 public:
  /**
   * @brief This virtual function is called by a publisher to notify the
   * subscriber about an event.
   * @param[in] obj The JSON object containing information about the event.
   */
  virtual void notify(const JsonObject& obj) = 0;
};

#endif
