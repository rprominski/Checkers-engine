#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "../include/PositionRater.h"
#include "../include/MoveFinder.h"
#include "../include/PositionDrawer.h"
#include "../include/Color.h"
#include "../include/EventListener.h"

using namespace std;


int main() {
    vector<int> clickMoves;
    MoveFinder moveFinder;
    PositionDrawer positionDrawer;
    string position = "xcxcxcxccxcxcxcxxcxcxcxcxxxxxxxxxxxxxxxxbxbxbxbxxbxbxbxbbxbxbxbx";
    char colorToMove, playerColor;
    int depth;

    /*cout << "Podaj glebokosc" << endl;
    cin >> depth;
    moveFinder.setMaxDepth(depth);

    cout << "Biale czy czarne? [b,c]" << endl;
    cin >> playerColor;

    bool whoMoves;
    if (playerColor == 'c') {
        colorToMove = 'b';
        whoMoves = 1;
    } else {
        colorToMove = 'c';
        whoMoves = 0;
    }
    */
    Board board;
    positionDrawer.drawPosition(board);
    EventListener eventListener(positionDrawer.getWindow());
    while(!eventListener.isEnd()) {
        eventListener.listen();
        positionDrawer.drawPosition(board);
    }
    /*
    while (1) {
        int fieldToColor;

        if (whoMoves) {
            moveFinder.findBestMove(position, colorToMove, 0);
            position = moveFinder.getPositionAfterMove(position, moveFinder.getBestMove());
            whoMoves = 0;
            positionDrawer.drawPosition(position, fieldToColor);
            al_flip_display();
        }



        vector<vector<int> > mvs = moveFinder.findMoves(position, playerColor);

        if (mvs.size() == 0)
            break;

        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            if (ev.mouse.button == 1) {
                fieldToColor = getFieldFromCords(ev.mouse.x, ev.mouse.y);
                clickMoves.push_back(fieldToColor);
                bool clear = 1;

                for (int it = 0; it < mvs.size(); it++) {
                    if (mvs[it] == clickMoves) {
                        position = moveFinder.getPositionAfterMove(position, clickMoves);

                        whoMoves = 1;
                        clickMoves.clear();
                        fieldToColor = -1;
                    }

                    bool equal = 1;
                    for (int j = 0; j < clickMoves.size(); j++) {
                        if (clickMoves[j] != mvs[it][j]) {
                            equal = 0;
                            break;
                        }
                    }
                    if (equal)
                        clear = 0;
                }

                if (clear)
                    clickMoves.clear();
            }

            if (ev.mouse.button == 2) {
                clickMoves.clear();
                fieldToColor = -1;
            }

            positionDrawer.drawPosition(position, fieldToColor);
            al_flip_display();
        }
        moveFinder.countPawns(position);
        if (moveFinder.noPawns())
            break;
    }
    sleep(5);
    */
   //
    return 0;
}
