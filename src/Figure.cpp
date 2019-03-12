//
// Created by rafal on 07.03.19.
//

#include "../include/Figure.h"

Figure::Figure() {
    color = NONE;
    type = NONE;
}

Color Figure::getColor() const {
    return color;
}

void Figure::setColor(Color color) {
    Figure::color = color;
}

Figure::Type Figure::getType() const {
    return type;
}

void Figure::setType(Type type) {
    Figure::type = type;
}