//
// Created by teeebor on 2017-12-26.
//

#pragma once


#include <vector>
#include <functional>
#include "utility.h"
#include "CustomEvent.h"

typedef void (*EventFun)(CustomEvent *,void *);

struct PROTON_API Subscription {
    const char *m_Name;
    std::vector<EventFun> m_Events;
    std::vector<void *> classes;

    Subscription(const char *name):m_Name(name){}

    const void fire(CustomEvent *e) {
        for(int i=0;i<m_Events.size();i++){
            LOG("SUB","CALLING EVENT");
            m_Events[i](e,classes[i]);
        }
    }

    void addEvent(EventFun callback) {

        LOG("EVENT","ADDING EVENT");
        LOG("EVENT",m_Name);
        m_Events.push_back(callback);
    }
};

class PROTON_API EventManager {
private:
    std::vector<Subscription *> m_Subscription;
private:
    EventManager() {}

public:
    Subscription *getSubscription(const char *name);

    static EventManager &getInstance();

    Subscription *createEvent(const char *name);

    void fire(const char *name, CustomEvent *e);

    bool subscribe(const char *name, EventFun callback, void *classPointer);
};
