#include<iostream>
#include<vector>
#include<windows.h>
using namespace std;

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

bool isLegal(int x, int y, string position)
{
    if(x<0 || y<0 || x>7 || y>7)
        return false;

    if(position[x+y*8]!='x')
        return false;

    return true;
}

int findCapturesForMen(string position, int field, int depth)
{
    cout<<field<<" "<<depth<<endl;
    for(int i=0;i<position.size();i++)
    {
        cout<<position[i];
        if((i+1)%8==0)
            cout<<endl;
    }
    int x,y,maxCaptures=depth;
    char color=position[field];
    x=field%8;
    y=(field-x)/8;

    if(color=='b')
    {
        if(isLegal(x-2,y-2,position) && (position[field-9]=='c' || position[field-9]=='C'))
        {
            string newPosition=position;
            newPosition[field-9]='x';
            newPosition[field-18]=position[field];
            newPosition[field]='x';
            maxCaptures=max(maxCaptures,findCapturesForMen(newPosition,field-18,depth+1));
        }

        if(isLegal(x+2,y-2,position) && (position[field-7]=='c' || position[field-7]=='C'))
        {
            string newPosition=position;
            newPosition[field-7]='x';
            newPosition[field-14]=position[field];
            newPosition[field]='x';
            maxCaptures=max(maxCaptures,findCapturesForMen(newPosition,field-14,depth+1));
        }

        if(isLegal(x-2,y+2,position) && (position[field+7]=='c' || position[field+7]=='C'))
        {
            string newPosition=position;
            newPosition[field+7]='x';
            newPosition[field+14]=position[field];
            newPosition[field]='x';
            maxCaptures=max(maxCaptures,findCapturesForMen(newPosition,field+14,depth+1));
        }

        if(isLegal(x+2,y+2,position) && (position[field+9]=='c' || position[field+9]=='C'))
        {
            string newPosition=position;
            newPosition[field+9]='x';
            newPosition[field+18]=position[field];
            newPosition[field]='x';
            maxCaptures=max(maxCaptures,findCapturesForMen(newPosition,field+18,depth+1));
        }
    }

    if(color=='c')
    {
        if(isLegal(x-2,y-2,position) && (position[field-9]=='b' || position[field-9]=='B'))
        {
            string newPosition=position;
            newPosition[field-9]='x';
            newPosition[field-18]=position[field];
            newPosition[field]='x';
            maxCaptures=max(maxCaptures,findCapturesForMen(newPosition,field-18,depth+1));
        }

        if(isLegal(x+2,y-2,position) && (position[field-7]=='b' || position[field-7]=='B'))
        {
            string newPosition=position;
            newPosition[field-7]='x';
            newPosition[field-14]=position[field];
            newPosition[field]='x';
            maxCaptures=max(maxCaptures,findCapturesForMen(newPosition,field-14,depth+1));
        }

        if(isLegal(x-2,y+2,position) && (position[field+7]=='b' || position[field+7]=='B'))
        {
            string newPosition=position;
            newPosition[field+7]='x';
            newPosition[field+14]=position[field];
            newPosition[field]='x';
            maxCaptures=max(maxCaptures,findCapturesForMen(newPosition,field+14,depth+1));
        }

        if(isLegal(x+2,y+2,position) && (position[field+9]=='b' || position[field+9]=='B'))
        {
            string newPosition=position;
            newPosition[field+9]='x';
            newPosition[field+18]=position[field];
            newPosition[field]='x';
            maxCaptures=max(maxCaptures,findCapturesForMen(newPosition,field+18,depth+1));
        }
    }

    return maxCaptures;
}

pair<int,vector<int> > findCapturesForKing(string position,int field, int depth, vector<int> moves, vector<pair<int,vector<int> > result)
{
    cout<<field<<" "<<depth<<endl;
    for(int i=0;i<position.size();i++)
    {
        cout<<position[i];
        if((i+1)%8==0)
            cout<<endl;
    }

    int x,y,captureField;
    pair<int,vector<int> > maxCaptures=make_pair(depth,moves);
    char color=position[field];
    bool capture;
    x=field%8;
    y=(field-x)/8;

    if(color=='B')
    {
        capture=0;
        for(int i=1;i<8;i++)
        {
            if(x-i<0 || y-i<0)
                break;

            if(position[field-i*9]=='c' || position[field-i*9]=='C')
                capture=1;

            if(capture)
            {
                if(!isLegal(x-i,y-i,position))
                    break;

                moves.push_back(field-i*9);
            }
        }

        capture=0;
        for(int i=1;i<8;i++)
        {
            if(x+i>7 || y-i<0)
                break;

            if(position[field-i*7]=='c' || position[field-i*7]=='C')
                capture=1;

            if(capture)
            {
                if(!isLegal(x+i,y-i,position))
                    break;

                moves.push_back(field-i*7);
            }
        }

        capture=0;
        for(int i=1;i<8;i++)
        {
            if(x-i<0 || y+i>7)
                break;

            if(position[field+i*7]=='c' || position[field+i*7]=='C')
                capture=1;

            if(capture)
            {
                if(!isLegal(x-i,y+i,position))
                    break;

                moves.push_back(field+i*7);
            }

        }

        capture=0;
        for(int i=1;i<8;i++)
        {
            if(x+i>7 || y+i>7)
                break;

            if(position[field+i*9]=='c' || position[field+i*9]=='C')
                capture=1;

            if(capture)
            {
                if(!isLegal(x+i,y+i,position))
                    break;

                moves.push_back(field+i*9);
            }
        }
    }

    if(color=='C')
    {
        capture=0;
        for(int i=1;i<8;i++)
        {
            if(x-i<0 || y-i<0)
                break;

            if(position[field-i*9]=='b' || position[field-i*9]=='B')
            {
                capture=1;
                captureField=field-i*9;
                i++;
            }

            if(capture)
            {
                if(!isLegal(x-i,y-i,position))
                    break;

                string newPosition=position;
                pair<int, vector<int> > help;
                vector<int> newMoves=moves;
                newMoves.push_back(field-i*9);
                newPosition[field-i*9]=position[field];
                newPosition[captureField]='x';
                newPosition[field]='x';
                help=findCapturesForKing(newPosition,field-i*9,depth+1,newMoves,result);

                if(maxCaptures.first==help.first)
                {
                        result.push_back(help);
                        cout<<" tutaj0 "<<result.size()<<endl;
                }

                if(maxCaptures<help)
                {
                    result.clear();
                    result.push_back(help);
                    maxCaptures=help;
                    cout<<" tam0 "<<result.size()<<endl;
                }
            }
        }

        capture=0;
        for(int i=1;i<8;i++)
        {
            if(x+i>7 || y-i<0)
                break;

            if(position[field-i*7]=='b' || position[field-i*7]=='B')
            {
                capture=1;
                captureField=field-i*7;
                i++;
            }

            if(capture)
            {
                if(!isLegal(x+i,y-i,position))
                    break;

                string newPosition=position;
                pair<int, vector<int> > help;
                vector<int> newMoves=moves;
                newMoves.push_back(field-i*7);
                newPosition[field-i*7]=position[field];
                newPosition[captureField]='x';
                newPosition[field]='x';
                help=findCapturesForKing(newPosition,field-i*7,depth+1,newMoves);

                if(maxCaptures.first==help.first)
                {
                        result.push_back(help);
                        cout<<" tutaj1 "<<result.size()<<endl;
                }
                if(maxCaptures<help)
                {
                    result.clear();
                    result.push_back(help);
                    maxCaptures=help;
                    cout<<" tam1 "<<result.size()<<endl;
                }
            }
        }

        capture=0;
        for(int i=1;i<8;i++)
        {
            if(x-i<0 || y+i>7)
                break;

            if(position[field+i*7]=='b' || position[field+i*7]=='B')
            {
                capture=1;
                captureField=field+i*7;
                i++;
            }

            if(capture)
            {
                if(!isLegal(x-i,y+i,position))
                    break;

                string newPosition=position;
                pair<int, vector<int> > help;
                vector<int> newMoves=moves;
                newMoves.push_back(field+i*7);
                newPosition[field+i*7]=position[field];
                newPosition[captureField]='x';
                newPosition[field]='x';
                help=findCapturesForKing(newPosition,field+i*7,depth+1,newMoves);

                if(maxCaptures.first==help.first)
                {
                        result.push_back(help);
                        cout<<" tutaj2 "<<result.size()<<endl;
                }

                if(maxCaptures<help)
                {
                    result.clear();
                    result.push_back(help);
                    maxCaptures=help;
                    cout<<" tam2 "<<result.size()<<endl;
                }
            }

        }

        capture=0;
        for(int i=1;i<8;i++)
        {
            if(x+i>7 || y+i>7)
                break;

            if(position[field+i*9]=='b' || position[field+i*9]=='B')
            {
                captureField=field+i*9;
                capture=1;
                i++;
            }

            if(capture)
            {
                if(!isLegal(x+i,y+i,position))
                    break;

                string newPosition=position;
                pair<int, vector<int> > help;
                vector<int> newMoves=moves;
                newMoves.push_back(field+i*9);
                newPosition[field+i*9]=position[field];
                newPosition[captureField]='x';
                newPosition[field]='x';
                help=findCapturesForKing(newPosition,field+i*9,depth+1,newMoves);

                if(maxCaptures.first==help.first)
                {
                        result.push_back(help);
                        cout<<" tutaj3 "<<result.size()<<endl;
                }

                if(maxCaptures<help)
                {
                    result.clear();
                    result.push_back(help);
                    maxCaptures=help;
                    cout<<" tam3 "<<result.size()<<endl;
                }
            }
        }
    }

    return maxCaptures;

}

vector<int> findCaptures(string position, char whoMoves)
{
    vector<int> bestMoves;
    int bestCaptures=0;

    for(int i=0;i<position.size();i++)
    {
        if(position[i]==whoMoves)
        {
            int help=findCapturesForMen(position,i,0);

            if(help>bestCaptures)
            {
                bestMoves.clear();
                bestMoves.push_back(i);
                bestCaptures=help;
            }

            if(help==bestCaptures)
                bestMoves.push_back(i);
        }

        if(position[i]==whoMoves-32)
        {
            int help;//=findCapturesForKing(position,i,0);

            if(help>bestCaptures)
            {
                bestMoves.clear();
                bestMoves.push_back(i);
                bestCaptures=help;
            }

            if(help==bestCaptures)
                bestMoves.push_back(i);
        }
    }

    return bestMoves;
}


int main()
{
    string position="xxxxxxxxxxxxxxxxxCxxxxxxxxxxxxxxxxxbxbxxxxxxxxxxxxxxxxxxxxxxxxxx";
    pair<int, vector<int> > para;
    para.second.push_back(17);
    para=findCapturesForKing(position,17,0,para.second);

    cout<<result.size()<<endl;
    for(int i=0;i<result.size();i++)
    {
        for(int j=0;j<result[i].second.size();j++)
            cout<<result[i].second[j]<<" ";
        cout<<endl;
    }
    return 0;
}
