#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "include/PositionRater.h"
#include "include/MoveFinder.h"
using namespace std;
/*void wyswietl(string position)
{
    for(int j=0;j<position.size();j++)
    {

        cout<<(position[j]=='x'? ' ' : position[j]);
        if((j+1)%8==0)
            cout<<endl;
    }
}

void wyswietl(vector<int> position)
{
    for(int j=0;j<position.size();j++)
    {
        cout<<position[j]<<" ";
    }
    cout<<endl<<endl;
}

void wyswietl(vector<vector<int> > tab)
{
    for(int j=0;j<tab.size();j++)
    {
        for(int k=0;k<tab[j].size();k++)
            cout<<tab[j][k]<<" ";
        cout<<endl;
    }
    cout<<endl<<endl;
} */

void drawRectangle(int x,int y, char color)
{
    if(color=='c')
        al_draw_filled_rectangle(x,y,x+100,y+100,al_map_rgb(0,0,0));

    if(color=='b')
        al_draw_filled_rectangle(x,y,x+100,y+100,al_map_rgb(255,255,255));

    if(color=='y')
        al_draw_filled_rectangle(x,y,x+100,y+100,al_map_rgb(255,255,0));
}
void drawMen(int x,int y,int color)
{
    if(color=='b')
        al_draw_filled_circle(x,y,20,al_map_rgba(0,0,255,100));

    if(color=='c')
        al_draw_filled_circle(x,y,20,al_map_rgba(255,0,0,100));
}

void drawKing(int x,int y,int color)
{
    if(color=='B')
        al_draw_filled_circle(x,y,20,al_map_rgb(122,44,200));

    if(color=='C')
        al_draw_filled_circle(x,y,20,al_map_rgb(200,122,44));
}

void drawBoard()
{
    int x,y;
    for(int i=0;i<64;i++)
    {
        x=i%8;
        y=(i-x)/8;

        if(y%2==0)
        {
            if(x%2==0)
                drawRectangle(x*100,y*100,'b');
            else
                drawRectangle(x*100,y*100,'c');
        }

        else
        {
            if(x%2==0)
                drawRectangle(x*100,y*100,'c');
            else
                drawRectangle(x*100,y*100,'b');
        }
    }
}

void drawPosition(string position,int f)
{
    drawBoard();

    int x,y;
    x=f%8;
    y=(f-x)/8;
    if(f!=-1)
    drawRectangle(x*100,y*100,'y');
    for(int i=0;i<position.size();i++)
    {
        x=i%8;
        y=(i-x)/8;

        if(position[i]=='b' || position[i]=='c')
            drawMen(x*100+50,y*100+50,position[i]);

        if(position[i]=='B' || position[i]=='C')
            drawKing(x*100+50,y*100+50,position[i]);
    }
}

int getFieldFromCords(int x,int y)
{
    return x/100+y/100*8;
}

int main()
{
    vector<int> clickMoves;
    MoveFinder moveFinder;
    string position="xcxcxcxccxcxcxcxxcxcxcxcxxxxxxxxxxxxxxxxbxbxbxbxxbxbxbxbbxbxbxbx";
    char colorToMove,playerColor;
    int depth;

    cout<<"Podaj glebokosc"<<endl;
    cin>>depth;
    moveFinder.maxDepth=depth;

    cout<<"Biale czy czarne? [b,c]"<<endl;
    cin>>playerColor;

    bool whoMoves;

    if(playerColor=='c')
    {
        colorToMove='b';
        whoMoves=1;
    }
    else
    {
        colorToMove='c';
        whoMoves=0;
    }

    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    ALLEGRO_KEYBOARD_STATE keyboard;
    ALLEGRO_DISPLAY *window=al_create_display(800,800);
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_mouse_event_source());

    while(1)
    {
        int fieldToColor;

        if(whoMoves)
        {
            moveFinder.findBestMove(position,colorToMove,0);
            position=moveFinder.getPositionAfterMove(position,moveFinder.getBestMove());
            whoMoves=0;
            drawPosition(position,fieldToColor);
            al_flip_display();
        }

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        vector<vector<int> > mvs=moveFinder.findMoves(position,playerColor);

        if(mvs.size()==0)
            break;

        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            if(ev.mouse.button==1)
            {
                fieldToColor=getFieldFromCords(ev.mouse.x,ev.mouse.y);
                clickMoves.push_back(fieldToColor);
                bool clear=1;

                for(int it=0;it<mvs.size();it++)
                {
                    if(mvs[it]==clickMoves)
                    {
                        position=moveFinder.getPositionAfterMove(position,clickMoves);

                        whoMoves=1;
                        clickMoves.clear();
                        fieldToColor=-1;
                    }

                    bool equal=1;
                    for(int j=0;j<clickMoves.size();j++)
                    {
                        if(clickMoves[j]!=mvs[it][j])
                        {
                            equal=0;
                            break;
                        }
                    }
                    if(equal)
                        clear=0;
                }

                if(clear)
                    clickMoves.clear();
            }

            if(ev.mouse.button==2)
            {
                clickMoves.clear();
                fieldToColor=-1;
            }

            drawPosition(position,fieldToColor);
            al_flip_display();
        }
        moveFinder.countPawns(position);
        if(moveFinder.noPawns())
            break;
    }
    sleep(5);

    al_destroy_display(window);
    return 0;
}
