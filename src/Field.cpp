//
// Created by rafal on 27.02.19.
//

#include "../include/Field.h"

Color Field::getColor() const {
    return color;
}

void Field::setColor(Color color) {
    Field::color = color;
}

const Figure &Field::getFigure() const {
    return figure;
}

void Field::setFigure(Figure figure) {
    Field::figure = figure;
}

int Field::getX() const {
    return x;
}

void Field::setX(int x) {
    Field::x = x;
}

int Field::getY() const {
    return y;
}

void Field::setY(int y) {
    Field::y = y;
}

Field::Field(Color color, const Figure &figure, int x, int y) : color(color), figure(figure), x(x), y(y) {}

Field::Field() {
    color = Color::NONE;
}
