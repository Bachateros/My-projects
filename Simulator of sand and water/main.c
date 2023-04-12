#include <stdio.h>
#include <stdlib.h>
#define _WIN32_WINNT 0x501
#include <windows.h>

#define width 100
#define hight 29
#define c_sand (char)176
#define c_water (char)219
#define c_space ' '
#define c_wall '#'

typedef char Tmap[hight][width];
Tmap map;
POINT mousePos;
POINT sellSize;
enum {s_sand,s_water,s_wall,s_last} substance = s_sand;
char subChar[]={c_sand,c_water,c_wall};
char* subName[] = {"sand","water","wall"};

POINT GetMousePos(HWND hwnd,POINT sellSz)
{
    static POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hwnd,&pt);
    pt.x/=sellSz.x;
    pt.y/=sellSz.y;
    return pt;
}

POINT GetSellSize(HWND hwnd)
{
    RECT rct;
    GetClientRect(hwnd,&rct);
    POINT sellSz;
    sellSz.x=(rct.right-rct.left)/width;
    sellSz.y=(rct.bottom-rct.top)/hight;
    return sellSz;
}

void ClearMap()
{
    memset(map,c_space,sizeof(map));
    map[hight-1][width-1]='\0';
}

void SetCurPos(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void ShowMap(Tmap map)
{
    SetCurPos(0,0);
    printf("%s",map[0]);
}

void ShowInfo()
{
    SetCurPos(0,hight);
    for(int i=0; i<s_last;i++)
        printf("%d-%s\t",i+1,subName[i]);
    printf("LButton-put %s  RButton-delete",subName[substance]);
}

char IfPointInMap(int x, int y)
{
    return !((x<0) || (y<0) || (x>width) || (y>hight));
}

void MoveSand(int x, int y)
{
    for(int i=0;i<=1;i+=(i==0?-1:2))
        if(IfPointInMap(x+i,y+1))
            if((map[y+1][x+i]==c_space)||
                (map[y+1][x+i]==c_water))
            {
                map[y][x]=map[y+1][x+i];
                map[y+1][x+i]=c_sand;
                break;
            }
}

Tmap maptmp;
char waterLevel;
POINT foundPoint;

void FindWaterPath(int x,int y)
{
    if(!IfPointInMap(x,y))return;

    if((y>=waterLevel)&&(y>foundPoint.y))
        if(maptmp[y][x]==c_space)
        {
            foundPoint.x=x;
            foundPoint.y=y;
        }
    if(maptmp[y][x]==c_water)
    {
        maptmp[y][x]=c_wall;
        FindWaterPath(x,y-1);
        FindWaterPath(x,y+1);
        FindWaterPath(x-1,y);
        FindWaterPath(x+1,y);
    }
}

void MoveWater(int x,int y)
{
    if(!IfPointInMap(x,y))return;

    if(map[y+1][x]==c_space)
    {
        map[y][x]=c_space;
        map[y+1][x]=c_water;
    }
    else if(map[y+1][x]==c_water)
    {
        waterLevel=y+1;
        foundPoint.y=-1;
        memcpy(maptmp,map,sizeof(map));
        FindWaterPath(x,y+1);
        if(foundPoint.y>=0)
        {
            map[foundPoint.y][foundPoint.x]=c_water;
            map[y][x]=c_space;
        }
    }
}

void MoveSubstance()
{
    for(int j=hight;j>=0;j--)
        for(int i=0;i<width;i++)
        {
            if(map[j][i]==c_sand)MoveSand(i,j);
            if(map[j][i]==c_water)MoveWater(i,j);
        }
}

void SelectSubstance()
{
    for(int i = 0; i<s_last;i++)
        if(GetKeyState('1' + i)<0)substance=i;
}

void PutSubstance(POINT pt)
{
    if(GetKeyState(VK_LBUTTON)<0)
        map[pt.y][pt.x]=subChar[substance];
    else if(GetKeyState(VK_RBUTTON)<0)
        map[pt.y][pt.x]=c_space;
}

int main()
{
    HWND hwnd = GetConsoleWindow();
    sellSize = GetSellSize(hwnd);
    ClearMap();
    do
    {
        mousePos = GetMousePos(hwnd,sellSize);

        SelectSubstance();
        PutSubstance(mousePos);
        MoveSubstance();

        ShowMap(map);
        ShowInfo();
        Sleep(50);
    }
    while(GetKeyState(VK_ESCAPE)>=0);
    return 0;
}
