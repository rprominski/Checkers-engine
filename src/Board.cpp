//
// Created by rafal on 27.02.19.
//

#include "../include/Board.h"
#include "../include/Color.h"

Board::Board() {
    size = 8;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Field field;
            Figure fgr;

            field.setColor(Color::WHITE);
            if (i % 2 + j % 2 == 1) {
                field.setColor(Color::BLACK);
            }

            if (i <= 2 && (i ^ j) % 2 == 1) {
                fgr.setType(fgr.MAN);
                fgr.setColor(Color::WHITE);
            }
            if (i >= size - 3 && (i ^ j) % 2 == 1) {
                fgr.setType(fgr.MAN);
                fgr.setColor(Color::BLACK);
            }
            field.setFigure(fgr);
            field.setX(j);
            field.setY(i);
            fields.push_back(field);
        }
    }
}

int Board::getSize() const {
    return size;
}

void Board::setSize(int size) {
    Board::size = size;
}

const std::vector<Field> &Board::getFields() const {
    return fields;
}

void Board::setFields(const std::vector<Field> &fields) {
    Board::fields = fields;
}
