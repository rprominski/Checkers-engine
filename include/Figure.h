//
// Created by rafal on 02.03.19.
//

#include "Color.h"

#ifndef HECKERS_ENGINE_FIGURE_H
#define HECKERS_ENGINE_FIGURE_H

#endif //HECKERS_ENGINE_FIGURE_H

class Figure {
public:
    enum Type {
        MAN,
        KING,
        NONE
    };
private:
    Color color;
    Type type;

public:
    Color getColor();

    void setColor(Color color);

    Type getType();

    void setType(Type type);

    Figure();
};


