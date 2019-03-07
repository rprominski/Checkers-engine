//
// Created by rafal on 27.02.19.
//

#include "../include/Board.h"
#include "../include/Color.h"

Board::Board() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Field field;
            Figure fgr;

            field.setColor(Color::WHITE);
            if (i % 2 + j % 2 == 1) {
                field.setColor(Color::BLACK);
            }

            if (i <= 2) {
                fgr.setType(fgr.MAN);
                fgr.setColor(Color::WHITE);
            }
            if (i > size - 3) {
                fgr.setType(fgr.MAN);
                fgr.setColor(Color::BLACK);
            }

            fields.push_back(field);
        }
    }
}
