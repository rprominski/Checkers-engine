#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "../include/PositionRater.h"
#include "../include/MoveFinder.h"
#include "../include/PositionDrawer.h"

using namespace std;

int getFieldFromCords(int x, int y) {
    return x / 100 + y / 100 * 8;
}

int main() {
    vector<int> clickMoves;
    MoveFinder moveFinder;
    PositionDrawer positionDrawer;
    string position = "xcxcxcxccxcxcxcxxcxcxcxcxxxxxxxxxxxxxxxxbxbxbxbxxbxbxbxbbxbxbxbx";
    char colorToMove, playerColor;
    int depth;

    cout << "Podaj glebokosc" << endl;
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

    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    ALLEGRO_KEYBOARD_STATE keyboard;
    ALLEGRO_DISPLAY *window = al_create_display(800, 800);
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_mouse_event_source());

    while (1) {
        int fieldToColor;

        if (whoMoves) {
            moveFinder.findBestMove(position, colorToMove, 0);
            position = moveFinder.getPositionAfterMove(position, moveFinder.getBestMove());
            whoMoves = 0;
            positionDrawer.drawPosition(position, fieldToColor);
            al_flip_display();
        }

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

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

    al_destroy_display(window);
    return 0;
}
