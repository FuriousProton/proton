
#include "../../../include/EventManager.h"
#include "../../../include/CustomEvent.h"

#include <cstring>

EventManager &EventManager::getInstance() {
    static EventManager inst;
    return inst;
}

Subscription *EventManager::createEvent(const char *name) {
    auto s = new Subscription(name);
    m_Subscription.push_back(s);
    return s;
}

bool EventManager::subscribe(const char *name, EventFun callback, void *classPointer) {
    auto s = getSubscription(name);
    if (s != nullptr) {
//        LOG("EVENT SUB","FOUND SUB");
        s->addEvent(callback);
        s->classes.push_back(classPointer);
        return true;
    }
    return false;
}

void EventManager::fire(const char *name, CustomEvent *e) {
//    LOG("FIRE EVENT",name);
    auto s = getSubscription(name);
    if (s != nullptr) {
//        LOG("EVENT","FOUND SUB");
        s->fire(e);
    }
}

Subscription *EventManager::getSubscription(const char *name) {
    for (auto s : m_Subscription) {
        if (std::strcmp(s->m_Name, name) == 0) {
            return s;
        }
    }
    return nullptr;
}