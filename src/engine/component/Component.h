//
// Created by teeebor on 2017-10-05.
//

#pragma once


namespace proton{
    class Entity;

    class Component {
    private:
        Entity *mpEntity;
    public:

        virtual void start();
        virtual void update();
        virtual void end();

        Entity &getEntity();

    protected:
        void setComoponent(Entity *e);
    };

}

