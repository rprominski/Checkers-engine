//
// Created by rafal on 12.03.19.
//

#include <allegro5/mouse.h>
#include <iostream>
#include <allegro5/haptic.h>
#include "../include/EventListener.h"

EventListener::EventListener(ALLEGRO_DISPLAY* display) {
    end = false;
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
}

void EventListener::listen() {
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        end = true;
    }
}

bool EventListener::isEnd() const {
    return end;
}
