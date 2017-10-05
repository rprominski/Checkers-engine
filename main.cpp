#include<iostream>
#include<vector>
#include<unistd.h>
using namespace std;
class abc{
public:
vector< vector<int> > moves;

double fieldBonus(char color, double bonus)
{
    if(color=='c' || color=='C')
        return -bonus;
    if(color=='b' || color=='B')
        return bonus;

    return 0.0;
}

double positionBonus(string position)
{
    double result=0;
    int bonus1[14]={1,3,5,7,8,23,24,39,40,55,56,58,60,62};
    int bonus2[10]={10,12,14,17,30,33,46,49,51,53};
    int bonus3[8]={19,21,26,28,35,37,42,44};

    for(int i=0;i<14;i++)
        result+=fieldBonus(position[bonus1[1]],0.4);

    for(int i=0;i<10;i++)
        result+=fieldBonus(position[bonus2[i]],0.75);

    for(int i=0;i<8;i++)
        result+=fieldBonus(position[bonus3[i]],1);


    for(int i=0;i<8;i++)
        result+=((position[i]=='c')? -1: 0);

    for(int i=8;i<16;i++)
        result+=((position[i]=='c')? -1: 5);

    for(int i=16;i<24;i++)
        result+=((position[i]=='c')? -2: 4);

    for(int i=24;i<32;i++)
        result+=((position[i]=='c')? -2: 3);

    for(int i=32;i<40;i++)
        result+=((position[i]=='c')? -3: 2);

    for(int i=40;i<48;i++)
        result+=((position[i]=='c')? -4: 2);

    for(int i=48;i<56;i++)
        result+=((position[i]=='c')? -5: 1);

    for(int i=56;i<64;i++)
        result+=((position[i]=='c')? 0: 1);

    return result;
}

double materialBonus(string position)
{
    double result=0;
    for(int i=0;i<64;i++)
    {
        if(position[i]=='c' || position[i]=='b')
            result+=fieldBonus(position[i],4);

        else
            result+=fieldBonus(position[i],20);
    }

    return result;
}

double ratePosition(string position)
{
    return positionBonus(position)+materialBonus(position);
}

bool isLegal(int x, int y, string position, bool emptyField)
{
    if(x<0 || y<0 || x>7 || y>7)
        return false;

    if(emptyField && position[x+y*8]!='x')
        return false;

    return true;
}

string getNewPositionForMen(string position, int xDirection, int yDirection, char color,int field)
{
    int x,y;

    x=field%8;
    y=(field-x)/8;

    if(color=='b')
    {
        if(!(isLegal(x+(xDirection*2),y+(yDirection*2),position,1) && (position[field+(8*yDirection+xDirection)]=='c' || position[field+(8*yDirection+xDirection)]=='C') ) )
            return "";

        else
        {
            position[field+(8*yDirection+xDirection)]='x';
            position[field+2*(8*yDirection+xDirection)]=position[field];
            position[field]='x';
            return position;
        }
    }

    if(color=='c')
    {
        if(!(isLegal(x+(xDirection*2),y+(yDirection*2),position,1) && (position[field+(8*yDirection+xDirection)]=='b' || position[field+(8*yDirection+xDirection)]=='B') ) )
            return "";

        else
        {
            position[field+(8*yDirection+xDirection)]='x';
            position[field+2*(8*yDirection+xDirection)]=position[field];
            position[field]='x';
            return position;
        }
    }
    return "";
}

void findCapturesForMen(string position, int field, vector<int> menMoves)
{
    menMoves.push_back(field);
   /* cout<<field<<endl;
    for(int i=0;i<position.size();i++)
    {
        cout<<position[i];
        if((i+1)%8==0)
            cout<<endl;
    } */
    int x,y;
    char color=position[field];

    if(getNewPositionForMen(position,-1,-1,color,field)!="")
        findCapturesForMen(getNewPositionForMen(position,-1,-1,color,field),field-18,menMoves);

    if(getNewPositionForMen(position,-1,+1,color,field)!="")
        findCapturesForMen(getNewPositionForMen(position,-1,+1,color,field),field+14,menMoves);

    if(getNewPositionForMen(position,+1,-1,color,field)!="")
        findCapturesForMen(getNewPositionForMen(position,+1,-1,color,field),field-14,menMoves);

    if(getNewPositionForMen(position,+1,+1,color,field)!="")
        findCapturesForMen(getNewPositionForMen(position,+1,+1,color,field),field+18,menMoves);

    if(moves.size()==0 && menMoves.size()!=0)
        moves.push_back(menMoves);
    else
    {
        if(moves[0].size()==menMoves.size())
            moves.push_back(menMoves);

        if(moves[0].size()<menMoves.size())
        {
            moves.clear();
            moves.push_back(menMoves);
        }
    }
}

void checkDirectionForCapture(string position, int field, int xDirection, int yDirection, char color, vector<int> kingMoves)
{
    bool capture=0;
    int captureField,x,y;
    x=field%8;
    y=(field-x)/8;

    if(color=='B')
    {
        for(int i=1;i<8;i++)
        {
            if(!isLegal(x+i*xDirection,y+i*yDirection,position,0))
                break;

            if(position[field+i*(yDirection*8+xDirection)]=='c' || position[field+i*(yDirection*8+xDirection)]=='C')
            {
                capture=1;
                captureField=field+i*(yDirection*8+xDirection);
                i++;
            }

            if(capture)
            {
                if(!isLegal(x+xDirection*i,y+yDirection*i,position,1))
                    break;

                string newPosition=position;
                newPosition[field+i*(yDirection*8+xDirection)]='B';
                newPosition[captureField]='x';
                newPosition[field]='x';
                findCapturesForKing(newPosition,field+i*(yDirection*8+xDirection),kingMoves);
            }
        }
    }

    if(color=='C')
    {
        for(int i=1;i<8;i++)
        {
            if(!isLegal(x+i*xDirection,y+i*yDirection,position,0))
                break;

            if(position[field+i*(yDirection*8+xDirection)]=='b' || position[field+i*(yDirection*8+xDirection)]=='B')
            {
                capture=1;
                captureField=field+i*(yDirection*8+xDirection);
                i++;
            }

            if(capture)
            {
                if(!isLegal(x+xDirection*i,y+yDirection*i,position,1))
                    break;

                string newPosition=position;
                newPosition[field+i*(yDirection*8+xDirection)]='C';
                newPosition[captureField]='x';
                newPosition[field]='x';
                findCapturesForKing(newPosition,field+i*(yDirection*8+xDirection),kingMoves);
            }
        }
    }
}

void findCapturesForKing(string position,int field, vector<int> kingMoves)
{
    kingMoves.push_back(field);

    /*cout<<field<<" "<<endl;
    for(int i=0;i<position.size();i++)
    {
        cout<<position[i];
        if((i+1)%8==0)
            cout<<endl;
    }*/

    int x,y,captureField;
    char color=position[field];
    bool capture;
    string newPosition;


    checkDirectionForCapture(position,field,-1,-1,color,kingMoves);
    checkDirectionForCapture(position,field,-1,+1,color,kingMoves);
    checkDirectionForCapture(position,field,+1,-1,color,kingMoves);
    checkDirectionForCapture(position,field,+1,+1,color,kingMoves);

    if(moves.size()==0 && kingMoves.size()!=0)
        moves.push_back(kingMoves);
    else
    {
        if(moves[0].size()==kingMoves.size())
            moves.push_back(kingMoves);

        if(moves[0].size()<kingMoves.size())
        {
            moves.clear();
            moves.push_back(kingMoves);
        }
    }
}

void findCaptures(string position)
{
    for(int i=0;i<position.size();i++)
    {
        if(position[i]=='b' || position[i]=='c')
            findCapturesForMen(position,i,vector<int>());

        if(position[i]=='B' || position[i]=='C')
            findCapturesForKing(position,i,vector<int>());
    }
}

void findMovesForMen(string position)
{
    for(int i=0;i<position.size();i++)
    {
        int x,y;
        x=i%8;
        y=(i-x)/8;

        if(position[i]=='c')
        {
            if(isLegal(x-1,y-1,position,1))
                moves.push_back(vector<int>(i, i-9));

            if(isLegal(x+1,y-1,position,1))
                moves.push_back(vector<int>(i, i-7));
        }

        if(position[i]=='b')
        {
            if(isLegal(x-1,y+1,position,1))
                moves.push_back(vector<int>(i, i+7));

            if(isLegal(x+1,y+1,position,1))
                moves.push_back(vector<int>(i, i+9));
        }
    }
}

void checkDirectionForMove(string position, int field, int xDirection, int yDirection)
{
    int x,y;
    x=field%8;
    y=(field-x)/8;

    for(int i=0;i<8;i++)
    {
        if(isLegal(x+i*xDirection,y+i*yDirection,position,1))
            moves.push_back(vector<int>(field,field+i*(8*yDirection+xDirection)));
    }
}

void findMovesForKings(string position)
{
    for(int i=0;i<position.size();i++)
    {
        checkDirectionForMove(position,i,-1,-1);
        checkDirectionForMove(position,i,-1,+1);
        checkDirectionForMove(position,i,+1,-1);
        checkDirectionForMove(position,i,+1,+1);
    }
}

};

int main()
{
    abc xyz;
    string position="xxxxxxxxxxxxxxxxxxxCxxxxxxxxbxxxxbxxxxxxxxxxbxxxxbxxxxxxxxxxxxxx";

    xyz.findCaptures(position);
    for(int i=0;i<xyz.moves.size();i++)
    {
        for(int j=0;j<xyz.moves[i].size();j++)
            cout<<xyz.moves[i][j]<<" ";

        cout<<endl;
    }
//    para=findCapturesForKing(position,17,0,para.second);

//    cout<<result.size()<<endl;
    return 0;
}//
