//
// Created by rafal on 27.02.19.
//

#ifndef HECKERS_ENGINE_POSITIONDRAWER_H
#define HECKERS_ENGINE_POSITIONDRAWER_H

#include <string>

class PositionDrawer {
    void drawBoard();

    void drawKing(int x, int y, int color);

    void drawMen(int x, int y, int color);

    void drawRectangle(int x, int y, char color);

public:
    void drawPosition(std::string position, int f);

};


#endif //HECKERS_ENGINE_POSITIONDRAWER_H
