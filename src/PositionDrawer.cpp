//
// Created by rafal on 27.02.19.
//

#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include "../include/PositionDrawer.h"

void PositionDrawer::drawPosition(std::string position, int f) {
    drawBoard();

    int x = f % 8;
    int y = (f - x) / 8;

    if (f != -1) {
        drawRectangle(x * 100, y * 100, 'y');
    }
    for (int i = 0; i < position.size(); i++) {
        x = i % 8;
        y = (i - x) / 8;

        if (position[i] == 'b' || position[i] == 'c') {
            drawMen(x * 100 + 50, y * 100 + 50, position[i]);
        }

        if (position[i] == 'B' || position[i] == 'C') {
            drawKing(x * 100 + 50, y * 100 + 50, position[i]);
        }
    }
}

void PositionDrawer::drawBoard() {
    int x, y;

    for (int i = 0; i < 64; i++) {
        x = i % 8;
        y = (i - x) / 8;

        if (y % 2 == 0) {
            if (x % 2 == 0) {
                drawRectangle(x * 100, y * 100, 'b');
            } else {
                drawRectangle(x * 100, y * 100, 'c');
            }
        } else {
            if (x % 2 == 0) {
                drawRectangle(x * 100, y * 100, 'c');
            } else {
                drawRectangle(x * 100, y * 100, 'b');
            }
        }
    }
}

void PositionDrawer::drawKing(int x, int y, int color) {
    if (color == 'B') {
        al_draw_filled_circle(x, y, 20, al_map_rgb(122, 44, 200));
    }
    if (color == 'C') {
        al_draw_filled_circle(x, y, 20, al_map_rgb(200, 122, 44));
    }
}

void PositionDrawer::drawMen(int x, int y, int color) {
    if (color == 'b') {
        al_draw_filled_circle(x, y, 20, al_map_rgba(0, 0, 255, 100));
    }
    if (color == 'c') {
        al_draw_filled_circle(x, y, 20, al_map_rgba(255, 0, 0, 100));
    }
}

void PositionDrawer::drawRectangle(int x, int y, char color) {
    if (color == 'c') {
        al_draw_filled_rectangle(x, y, x + 100, y + 100, al_map_rgb(0, 0, 0));
    }
    if (color == 'b') {
        al_draw_filled_rectangle(x, y, x + 100, y + 100, al_map_rgb(255, 255, 255));
    }
    if (color == 'y') {
        al_draw_filled_rectangle(x, y, x + 100, y + 100, al_map_rgb(255, 255, 0));
    }
}