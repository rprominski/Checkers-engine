//
// Created by rafal on 27.02.19.
//

#ifndef HECKERS_ENGINE_BOARD_H
#define HECKERS_ENGINE_BOARD_H

#include <vector>
#include "Field.h"

class Board {
    int size;
    std::vector<Field> fields;

public:
    Board();
};


#endif //HECKERS_ENGINE_BOARD_H
