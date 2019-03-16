#pragma once

#include <map>
#include <list>
#include <typeindex>

struct PROTON_API Event{};

struct PROTON_API DisplayEvent : public Event {
    DisplayEvent(double x, double y): width {x}, height{y} {}
    double width, height;
};


// This is the interface for MemberFunctionHandler that each specialization will use
class PROTON_API HandlerFunctionBase {
public:
    // Call the member function
    void exec(Event *evnt) {
        call(evnt);
    }

private:
    // Implemented by MemberFunctionHandler
    virtual void call(Event *evnt) = 0;
};

template<class T, class EventType>
class PROTON_API MemberFunctionHandler : public HandlerFunctionBase {
public:
    typedef void (T::*MemberFunction)(EventType *);

    MemberFunctionHandler(T *instance, MemberFunction memberFunction) : instance{instance},
                                                                        memberFunction{memberFunction} {};

    void call(Event *evnt) {
        // Cast event to the correct type and call member function
        (instance->*memberFunction)(static_cast<EventType *>(evnt));
    }

private:
    // Pointer to class instance
    T *instance;

    // Pointer to member function
    MemberFunction memberFunction;
};

typedef std::list<HandlerFunctionBase *> HandlerList;

class PROTON_API EventBus {

public:
    static EventBus& getInstance() {
        static EventBus inst;
        return inst;
    }

    template<typename EventType>
    void fire(EventType *evnt) {
        HandlerList *handlers = subscribers[typeid(EventType)];

        if (handlers == nullptr) {
            return;
        }

        for (auto &handler : *handlers) {
            if (handler != nullptr) {
                handler->exec(evnt);
            }
        }
    }

    template<class T, class EventType>
    void subscribe(T *instance, void (T::*memberFunction)(EventType *)) {
        HandlerList *handlers = subscribers[typeid(EventType)];

        //First time initialization
        if (handlers == nullptr) {
            handlers = new HandlerList();
            subscribers[typeid(EventType)] = handlers;
        }

        handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
    }

private:
    std::map<std::type_index, HandlerList *> subscribers;
};
