//
// Created by rafal on 12.03.19.
//

#ifndef HECKERS_ENGINE_EVENTLISTENER_H
#define HECKERS_ENGINE_EVENTLISTENER_H


#include <allegro5/events.h>

class EventListener {
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    bool end;
public:
    void listen();

    EventListener(ALLEGRO_DISPLAY* display);

    bool isEnd() const;
};


#endif //HECKERS_ENGINE_EVENTLISTENER_H
