//
// Created by rafal on 27.02.19.
//

#ifndef HECKERS_ENGINE_FIELD_H
#define HECKERS_ENGINE_FIELD_H

#include "Color.h"
#include "Figure.h"

class Field {
    Color color;
    Figure figure;
    int x;
    int y;
public:
    Color getColor() const;

    void setColor(Color color);

    const Figure &getFigure() const;

    void setFigure(Figure figure);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    Field(Color color, const Figure &figure, int x, int y);

    Field();
};


#endif //HECKERS_ENGINE_FIELD_H
