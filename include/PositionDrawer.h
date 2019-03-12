//
// Created by rafal on 27.02.19.
//

#ifndef HECKERS_ENGINE_POSITIONDRAWER_H
#define HECKERS_ENGINE_POSITIONDRAWER_H

#include <string>
#include "Color.h"
#include "Board.h"
#include <allegro5/allegro.h>

class PositionDrawer {
    ALLEGRO_DISPLAY *window;
    int fieldSize = 100;
    int figureSize;
    int width;
    void drawFigure(Field field);

    void drawRectangle(int x, int y, Color color);

public:
    void drawPosition(Board board);

    PositionDrawer(int width = 8);

    ALLEGRO_DISPLAY *getWindow() const;

    virtual ~PositionDrawer();

};


#endif //HECKERS_ENGINE_POSITIONDRAWER_H
