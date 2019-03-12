//
// Created by rafal on 27.02.19.
//

#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "../include/PositionDrawer.h"
#include "../include/Color.h"

void PositionDrawer::drawPosition(Board board) {
    for (auto i : board.getFields()) {
        drawRectangle(i.getX(), i.getY(), i.getColor());
        if (i.getFigure().getType() != Figure::NONE) {
            drawFigure(i);
        }
    }
    al_flip_display();
}

void PositionDrawer::drawFigure(Field field) {
    int x = field.getX() * fieldSize + fieldSize / 2;
    int y = field.getY() * fieldSize + fieldSize / 2;
    Color color = field.getFigure().getColor();

    if (field.getFigure().getType() == Figure::KING) {
        if (color == WHITE) {
            al_draw_filled_circle(x, y, figureSize, al_map_rgb(122, 44, 200));
        }
        if (color == BLACK) {
            al_draw_filled_circle(x, y, figureSize, al_map_rgb(200, 122, 44));
        }
    } else {
        if (color == WHITE) {
            al_draw_filled_circle(x, y, figureSize, al_map_rgb(0, 0, 255));
        }
        if (color == BLACK) {
            al_draw_filled_circle(x, y, figureSize, al_map_rgb(255, 0, 0));
        }
    }
}

void PositionDrawer::drawRectangle(int x, int y, Color color) {
    x *= fieldSize;
    y *= fieldSize;

    if (color == BLACK) {
        al_draw_filled_rectangle(x, y, x + fieldSize, y + fieldSize, al_map_rgb(0, 0, 0));
    }
    if (color == WHITE) {
        al_draw_filled_rectangle(x, y, x + fieldSize, y + fieldSize, al_map_rgb(255, 255, 255));
    }
    if (color == YELLOW) {
        al_draw_filled_rectangle(x, y, x + fieldSize, y + fieldSize, al_map_rgb(255, 255, 0));
    }
}

PositionDrawer::PositionDrawer(int width) {
    figureSize = fieldSize / 4;
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    ALLEGRO_KEYBOARD_STATE keyboard;
    window = al_create_display(width * fieldSize, width * fieldSize);
}

PositionDrawer::~PositionDrawer() {
    al_destroy_display(window);
}

ALLEGRO_DISPLAY *PositionDrawer::getWindow() const {
    return window;
}
