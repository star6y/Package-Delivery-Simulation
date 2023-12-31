#include "IPublish.h"

void IPublish::subscribe(ISubscribe* s) { subscribers.push_back(s); }

void IPublish::unsubscribe(ISubscribe* s) {
  for (auto i = subscribers.begin(); i != subscribers.end();) {
    if (*i == s) {
      i = subscribers.erase(i);
    } else {
      ++i;
    }
  }
}

void IPublish::notifySubscribers(const JsonObject& obj) {
  for (ISubscribe* subscriber : subscribers) {
    subscriber->notify(obj);
  }
}
